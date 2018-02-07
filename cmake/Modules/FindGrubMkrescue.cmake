find_program(GRUB_MKRESCUE grub-mkrescue)
if(NOT GRUB_MKRESCUE)
  message(FATAL_ERROR "Missing required tool: grub-mkrescue")
endif()
