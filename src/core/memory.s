.section .text
.code64

.global _set_memory_byte
_set_memory_byte:
  push %rbp
  mov %rsp, %rbp
  mov %rsi, %rax
  mov %rdx, %rcx

  rep stosb

  pop %rbp
  ret

.global _set_memory_word
_set_memory_word:
  push %rbp
  mov %rsp, %rbp
  mov %rsi, %rax
  mov %rdx, %rcx

  rep stosw

  pop %rbp
  ret

.global _set_memory_double_word
_set_memory_double_word:
  push %rbp
  mov %rsp, %rbp
  mov %rsi, %rax
  mov %rdx, %rcx

  rep stosl

  pop %rbp
  ret

.global _set_memory_quad_word
_set_memory_quad_word:
  push %rbp
  mov %rsp, %rbp
  mov %rsi, %rax
  mov %rdx, %rcx

  rep stosq

  pop %rbp
  ret

.global _copy_memory_byte
_copy_memory_byte:
  push %rbp
  mov %rsp, %rbp
  mov %rdx, %rcx

  rep movsb

  pop %rbp
  ret

.global _copy_memory_word
_copy_memory_word:
  push %rbp
  mov %rsp, %rbp
  mov %rdx, %rcx

  rep movsw

  pop %rbp
  ret

.global _copy_memory_double_word
_copy_memory_double_word:
  push %rbp
  mov %rsp, %rbp
  mov %rdx, %rcx

  rep movsd

  pop %rbp
  ret

.global _copy_memory_quad_word
_copy_memory_quad_word:
  push %rbp
  mov %rsp, %rbp
  mov %rdx, %rcx

  rep movsq

  pop %rbp
  ret
