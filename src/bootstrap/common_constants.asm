; vim: ft=nasm et ts=2 sw=2

cVgaTextBufferAddress equ 0xb8000
cVgaTextBufferBlankWord equ 0x0f200f200f200f20
cVgaTextBufferNumberOfQuads equ 500
cVgaTextBufferColumns equ 80
cVgaTextBufferRows equ 25
cTwoMegaBytes equ (1 << 21)
cPagePresentBit equ (1 << 0)
cPageWritableBit equ (1 << 1)
cPageHugePageBit equ (1 << 7)
