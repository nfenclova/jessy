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

; @brief Set the memory pointed to by @p destination to @p count copies of @p value
;
; @param destination  The destination memory location  @rdi
; @param value        The value to copy                @rsi
; @param count        The amount of copies             @rdx
;
; _set_memory_double_word(uint32_t volatile * destination, uint32_t const value, size_t const count)
global _set_memory_double_word:function
_set_memory_double_word:
  push rbp
  mov rbp, rsp
  mov rax, rsi
  mov rcx, rdx

  rep stosd

  pop rbp
  ret

; @brief Set the memory pointed to by @p destination to @p count copies of @p value
;
; @param destination  The destination memory location  @rdi
; @param value        The value to copy                @rsi
; @param count        The amount of copies             @rdx
;
; _set_memory_quad_word(uint64_t volatile * destination, uint64_t const value, size_t const count)
global _set_memory_quad_word:function
_set_memory_quad_word:
  push rbp
  mov rbp, rsp
  mov rax, rsi
  mov rcx, rdx

  rep stosq

  pop rbp
  ret

; @brief Copy @p count bytes of memory pointed to by @p source to @p destination
;
; @param destination  The destination memory location  @rdi
; @param source       The source memory location       @rsi
; @param count        The number of bytes to copy      @rdx
;
; _set_memory_byte(uint8_t volatile * destination, uint8_t volatile const * source, size_t const count)
global _copy_memory_byte:function
_copy_memory_byte:
  push rbp
  mov rbp, rsp
  mov rcx, rdx

  rep movsb

  pop rbp
  ret

; @brief Copy @p count words of memory pointed to by @p source to @p destination
;
; @param destination  The destination memory location  @rdi
; @param source       The source memory location       @rsi
; @param count        The number of words to copy      @rdx
;
; _set_memory_byte(uint16_t volatile * destination, uint16_t volatile const * source, size_t const count)
global _copy_memory_word:function
_copy_memory_word:
  push rbp
  mov rbp, rsp
  mov rcx, rdx

  rep movsw

  pop rbp
  ret

; @brief Copy @p count dwords of memory pointed to by @p source to @p destination
;
; @param destination  The destination memory location  @rdi
; @param source       The source memory location       @rsi
; @param count        The number of dwords to copy     @rdx
;
; _set_memory_byte(uint32_t volatile * destination, uint32_t volatile const * source, size_t const count)
global _copy_memory_double_word:function
_copy_memory_double_word:
  push rbp
  mov rbp, rsp
  mov rcx, rdx

  rep movsd

  pop rbp
  ret

; @brief Copy @p count qwords of memory pointed to by @p source to @p destination
;
; @param destination  The destination memory location  @rdi
; @param source       The source memory location       @rsi
; @param count        The number of qwords to copy     @rdx
;
; _set_memory_byte(uint64_t volatile * destination, uint64_t volatile const * source, size_t const count)
global _copy_memory_quad_word:function
_copy_memory_quad_word:
  push rbp
  mov rbp, rsp
  mov rcx, rdx

  rep movsq

  pop rbp
  ret
