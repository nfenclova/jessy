# vim: ft=cmake ts=2 sw=2 et

string(APPEND
  CMAKE_EXE_LINKER_FLAGS
  " -T ${CMAKE_CURRENT_SOURCE_DIR}/src/kernel.ld"
  )
