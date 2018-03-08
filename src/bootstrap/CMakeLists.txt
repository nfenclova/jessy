# vim: ft=cmake ts=2 sw=2 et

include_directories("${CMAKE_CURRENT_SOURCE_DIR}")
add_library(bootstrap OBJECT
  "boot.asm"
  "multiboot_header.asm"
  "transition.asm"
  )
