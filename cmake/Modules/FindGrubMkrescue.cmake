# vim: ft=cmake ts=2 sw=2 et

find_program(GRUB_MKRESCUE
  "grub-mkrescue"
  )
if(NOT GRUB_MKRESCUE)
  message(FATAL_ERROR "Missing required tool: grub-mkrescue")
endif()
