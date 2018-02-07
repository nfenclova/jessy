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

stack_bottom:
  resb 64
stack_top:

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
  mov dword [0xb8000], 0x2f4b2f4f

  call check_loaded_by_multiboot
  call check_cpuid_is_supported
  call check_long_mode_is_supported

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
