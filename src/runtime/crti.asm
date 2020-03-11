; vim: ft=nasm ts=2 sw=2 et


section .init
bits 64
global _init

_init:
  push rbp
  mov rbp, rsp

section .fini
bits 64
global _fini

_fini:
  push rbp
  mov rbp, rsp
