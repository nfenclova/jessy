.section .bs_mbh, "a"
.align 64

header_start:
.Lmagic:
    .long 0xe85250d6
.Larchitecture:
    .long 0
.Llength:
    .long header_end - header_start
.Lchecksum:
    .long 0x100000000 - (0xe85250d6 + 0 + (header_end - header_start))
.Lend:
    .int 0
    .int 0
    .long 8
header_end:
