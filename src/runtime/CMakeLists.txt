# vim: ft=cmake ts=2 sw=2 et

add_library(runtime_init OBJECT
  "crti.asm"
  )

add_library(runtime_end OBJECT
  "crtn.asm"
  )
