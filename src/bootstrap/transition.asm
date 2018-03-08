; vim: ft=nasm et ts=2 sw=2

%include "/common_constants.asm"

extern kernel_main
extern multiboot_information_pointer

section .bs_text progbits alloc exec nowrite
bits 64

global _transition:function
_transition:
  xor ax, ax
  mov ss, ax
  mov ds, ax
  mov es, ax
  mov fs, ax
  mov gs, ax

  mov rax, cVgaTextBufferBlankWord
  mov rdi, cVgaTextBufferAddress
  mov rcx, cVgaTextBufferNumberOfQuads
  rep stosq

  mov rdi, [multiboot_information_pointer]
  call kernel_main
  hlt
