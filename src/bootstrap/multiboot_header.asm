; vim: ft=nasm et ts=2 sw=2

section .bs_mbh progbits alloc noexec nowrite align=64

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
