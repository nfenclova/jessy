; vim: ft=nasm et ts=2 sw=2

extern kernel_main
global _start

OK equ 0x2f4b2f4f

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

msg_panic: db "PANIC: ",0
msg_multiboot: db "NOT LOADED BY MULTIBOOT2 LOADER",0
msg_cpuid: db "CPUID INSTRUCTION NOT SUPPORTED",0
msg_longmode: db "LONG-MODE NOT SUPPORTED",0

section .text
bits 32

_panic:
  xor ecx, ecx
  mov byte bl, [msg_panic]
.loop:
  mov byte [0xb8000 + ecx * 2], bl
  mov byte [0xb8000 + ecx * 2 + 1], 0x4f
  inc ecx
  mov byte bl, [msg_panic + ecx]
  cmp bl, 0
  jne .loop

  xor edx, edx
  mov byte bl, [eax]
.print:
  mov byte [0xb8000 + ecx * 2], bl
  mov byte [0xb8000 + ecx * 2 + 1], 0x4f
  inc ecx
  inc edx
  mov byte bl, [eax + edx]
  cmp bl, 0
  jne .print

  hlt

_start:
  mov esp, stack_top

  call check_loaded_by_multiboot
  call check_cpuid_is_supported
  call check_long_mode_is_supported
  call initialize_page_table_structure
  call enable_paging

  lgdt [gdt.ptr]

  jmp gdt.code:_start_long

  mov dword [0xb8000], 0x2f4b2f4f
  hlt

check_loaded_by_multiboot:
  cmp eax, 0x36d76289
  jne .error
  ret
.error:
  mov eax, msg_multiboot
  jmp _panic

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
  mov eax, msg_cpuid
  jmp _panic

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
  mov eax, msg_longmode
  jmp _panic

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

.print_okay:
  mov rax, 0x2f592f412f4b2f4f
  mov qword [0xb8000], rax

.enter_kernel:
  call kernel_main
  hlt
