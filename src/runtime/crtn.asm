; vim: ft=nasm ts=2 sw=2 et

section .init
bits 64
  mov rsp,rbp
  pop rbp
  ret

section .fini
bits 64
  mov rsp,rbp
  pop rbp
  ret
