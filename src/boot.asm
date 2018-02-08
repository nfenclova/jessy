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
  dq (1<<43) | (1<<44) | (1<<47) | (1<<53)
.ptr:
  dw $ - gdt - 1
  dq gdt

section .text
bits 32

_panic:
  mov dword [0xb8000], 0x4f524f45
  mov dword [0xb8004], 0x4f3a4f52
  mov dword [0xb8008], 0x4f204f20
  mov byte  [0xb800a], al
  hlt

_start:
  mov esp, stack_top

  call check_loaded_by_multiboot
  call check_cpuid_is_supported
  call check_long_mode_is_supported
  call initialize_page_table_structure
  call enable_paging

  lgdt [gdt.ptr]

  mov dword [0xb8000], 0x2f4b2f4f
  call kernel_main
  hlt

check_loaded_by_multiboot:
  cmp eax, 0x36d76289
  jne .error
  ret
.error:
  mov al, "m"
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
  mov al, "c"
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
  mov al, "l"
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
