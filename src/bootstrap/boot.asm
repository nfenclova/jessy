; vim: ft=nasm et ts=2 sw=2

extern kernel_main
global _start

BLANK64 equ 0x0f200f200f200f20
VGABASE equ 0xb8000
NOFVGAQ equ 500

section .multiboot_header

header_start:
.magic:
    dd 0xe85250d6
.architecture:
    dd 0
.length:
    dd header_end - header_start
.checksum:
    dd 0x100000000 - (0xe85250d6 + 0 + (header_end - header_start))
.end:
    dw 0
    dw 0
    dd 8
header_end:

section .bss
align 4096

plm4:
  resb 4096
pdp:
  resb 4096
pd:
  resb 4096
stack_bottom:
  resb 64
stack_top:

section .rodata
gdt:
  dq 0
.code: equ $ - gdt
  dq (1<<43) | (1<<44) | (1<<47) | (1<<53)
.ptr:
  dw $ - gdt - 1
  dq gdt

msg_panic:
  db "PANIC: ",0
msg_multiboot:
  db "NOT LOADED BY MULTIBOOT2 LOADER",0
msg_cpuid:
  db "CPUID INSTRUCTION NOT SUPPORTED",0
msg_longmode:
  db "LONG-MODE NOT SUPPORTED",0

section .data
vga_buffer:
  dd VGABASE
 
section .text
bits 32

_print:
  push ebp
  mov ebp, esp

  push ebx
  push esi

  mov eax, [ebp + 8]
  mov ebx, [ebp + 12]
  mov ecx, 0
  mov esi, [vga_buffer]

.loop:
  mov byte dl, [ebx + ecx]
  test dl, dl
  je .store_new_buffer_address
  mov byte [esi + ecx * 2], dl
  mov byte [esi + ecx * 2 + 1], al
  inc ecx
  jmp .loop

.store_new_buffer_address:
  shl ecx, 1
  add [vga_buffer], ecx

.leave:
  pop esi
  pop ebx
  mov esp, ebp
  pop ebp
  ret

_panic:
  push ebp
  mov ebp, esp

  push msg_panic
  push 0x4f
  call _print
  add esp, 8

  push dword [ebp + 8]
  push 0x4f
  call _print
  add esp, 8

  hlt

_start:
  mov esp, stack_top
  mov ebp, esp

  call check_loaded_by_multiboot
  call check_cpuid_is_supported
  call check_long_mode_is_supported
  call initialize_page_table_structure
  call enable_paging

  lgdt [gdt.ptr]

  jmp gdt.code:_start_long

  hlt

check_loaded_by_multiboot:
  cmp eax, 0x36d76289
  jne .error
  ret
.error:
  push msg_multiboot
  call _panic

check_cpuid_is_supported:
  pushfd
  pop eax
  mov ecx, eax

  xor eax, 1 << 21
  push eax
  popfd

  pushfd
  pop eax

  push ecx
  popfd

  cmp eax,ecx
  je .error
  ret
.error:
  push msg_cpuid
  call _panic

check_long_mode_is_supported:
  mov eax, 0x80000000
  cpuid
  cmp eax, 0x80000001
  jb .error

  mov eax, 0x80000001
  cpuid
  test edx, 1 << 29
  jz .error
  ret
.error:
  push msg_longmode
  call _panic

initialize_page_table_structure:
  mov eax, pdp
  or eax, 0x3
  mov [plm4], eax

  mov eax, pd
  or eax, 0x3
  mov [pdp], eax

  xor ecx, ecx
.map_pt_pages:
  mov eax, 0x20000
  mul ecx
  or  eax, 0x83
  mov [pd + ecx * 8], eax

  inc ecx
  cmp ecx, 512
  jne .map_pt_pages

  ret

enable_paging:
  mov eax, plm4
  mov cr3, eax

  mov eax, cr4
  or eax, 1 << 5
  mov cr4, eax

  mov ecx, 0xC0000080
  rdmsr
  or eax, 1 << 8
  wrmsr

  mov eax, cr0
  or eax, 1 << 31
  mov cr0, eax

  ret

section .text
bits 64

_start_long:
.reload_segment_registers:
  xor ax, ax
  mov ss, ax
  mov ds, ax
  mov es, ax
  mov fs, ax
  mov gs, ax

  call _clear_vga_buffer

.enter_kernel:
  call kernel_main
  hlt

_clear_vga_buffer:
  push rbp
  mov rbp, rsp
  push rdi

  mov rdi, VGABASE
  mov rcx, NOFVGAQ
  mov rax, BLANK64
  rep stosq

  pop rdi
  pop rbp
  ret
