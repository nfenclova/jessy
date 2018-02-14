; vim: ft=nasm et ts=2 sw=2

global _set_memory_byte:function
global _set_memory_word:function

section .text
bits 64

; Set the memory pointed to by `rdi` to `rdx` copies of `rsi`
; _set_memory_byte(unsigned char * (rdi), unsigned char (rsi), size_t (rdx))
_set_memory_byte:
  push rbp
  mov rbp, rsp
  mov rax, rsi
  mov rcx, rdx

  rep stosb

  pop rbp
  ret

; Set the memory pointed to by `rdi` to `rdx` copies of `rsi`
; _set_memory_word(uint16_t * (rdi), uint16_t (rsi), size_t (rdx))
_set_memory_word:
  push rbp
  mov rbp, rsp
  mov rax, rsi
  mov rcx, rdx

  rep stosw

  pop rbp
  ret
