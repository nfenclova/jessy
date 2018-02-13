# vim: ft=cmake ts=2 sw=2 et

include("FindPackageHandleStandardArgs")

find_program(GRUB_MKRESCUE
  "grub-mkrescue"
  )
if(NOT GRUB_MKRESCUE)
  message(FATAL_ERROR "Missing required tool: grub-mkrescue")
endif()

find_package_handle_standard_args(grub-mkrescue DEFAULT_MSG
  GRUB_MKRESCUE
  )
