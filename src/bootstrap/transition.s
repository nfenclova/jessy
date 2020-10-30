.include "bootstrap/common_constants.s"

.extern _init
.extern kernel_main
.extern multiboot_information_pointer

.section .bs_text, "ax", @progbits
.code64

.global _transition
_transition:
  xor %ax, %ax
  mov %ax, %ss
  mov %ax, %ds
  mov %ax, %es
  mov %ax, %fs
  mov %ax, %gs

  mov $cVgaTextBufferBlankWord, %rax
  mov $cVgaTextBufferAddress, %rdi
  mov $cVgaTextBufferNumberOfQuads, %rcx
  rep stosq

  call _init

  mov multiboot_information_pointer, %rdi
  call kernel_main
  hlt
