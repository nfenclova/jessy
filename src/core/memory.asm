; vim: ft=nasm et ts=2 sw=2

; @file memory.asm
; @ingroup os_core
; @brief Low-level Memory Operations
;
; This file contains definitions for simple, low-level memory operations.
;
; @since 0.1.0
; @author Natalia Fenclová

section .text
bits 64

; @brief Set the memory pointed to by @p destination to @p count copies of @p value
;
; @param destination  The destination memory location  @rdi
; @param value        The value to copy                @rsi
; @param count        The amount of copies             @rdx
;
; _set_memory_byte(uint8_t volatile * destination, uint8_t const value, size_t const count)
global _set_memory_byte:function
_set_memory_byte:
  push rbp
  mov rbp, rsp
  mov rax, rsi
  mov rcx, rdx

  rep stosb

  pop rbp
  ret

; @brief Set the memory pointed to by @p destination to @p count copies of @p value
;
; @param destination  The destination memory location  @rdi
; @param value        The value to copy                @rsi
; @param count        The amount of copies             @rdx
;
; _set_memory_word(uint16_t volatile * destination, uint16_t const value, size_t const count)
global _set_memory_word:function
_set_memory_word:
  push rbp
  mov rbp, rsp
  mov rax, rsi
  mov rcx, rdx

  rep stosw

  pop rbp
  ret
