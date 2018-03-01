# vim: ft=cmake ts=2 sw=2 et

add_library(multiboot OBJECT
  "boot_command_line.cpp"
  "boot_loader_name.cpp"
  "information.cpp"
  )
