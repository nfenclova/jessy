; vim: ft=nasm et ts=2 sw=2

extern kernel_main
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


section .text
bits 32

global _start
_start:
  mov dword [0xb8000], OK
  call kernel_main
  cli
  hlt
