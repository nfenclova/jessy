# vim: ft=cmake ts=2 sw=2 et

add_subdirectory("vga")

add_library(kern_objs OBJECT
  "boot.asm"
  "main.cpp"
  )

add_library(crt_init OBJECT
  "crti.asm"
  )

add_library(crt_end OBJECT
  "crtn.asm"
  )

add_executable(${PROJECT_NAME}
  $<TARGET_OBJECTS:crt_init>
  ${CROSS_GCC_CRTBEGIN}
  $<TARGET_OBJECTS:kern_objs>
  $<TARGET_OBJECTS:vga>
  ${CROSS_GCC_CRTEND}
  $<TARGET_OBJECTS:crt_end>
  )

target_link_libraries(${PROJECT_NAME}
  gcc
  )

set_target_properties(${PROJECT_NAME}
  PROPERTIES LINK_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/kernel.ld"
  )

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
  COMMAND "${CMAKE_OBJCOPY}"
  ARGS --only-keep-debug "$<TARGET_FILE:${PROJECT_NAME}>" ${CMAKE_BINARY_DIR}/debug_info.sym
  BYPRODUCTS ${CMAKE_BINARY_DIR}/debug_info.sym
  )

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
  COMMAND "${CMAKE_STRIP}"
  ARGS --strip-debug "$<TARGET_FILE:${PROJECT_NAME}>"
  )
