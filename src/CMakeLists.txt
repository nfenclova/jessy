# vim: ft=cmake ts=2 sw=2 et

add_subdirectory("bootstrap")
add_subdirectory("core")
add_subdirectory("kernel")
add_subdirectory("runtime")
add_subdirectory("vga")

add_executable(${PROJECT_NAME}
  $<TARGET_OBJECTS:runtime_init>
  ${CROSS_GCC_CRTBEGIN}

  $<TARGET_OBJECTS:bootstrap>
  $<TARGET_OBJECTS:core>
  $<TARGET_OBJECTS:kernel>
  $<TARGET_OBJECTS:vga>

  ${CROSS_GCC_CRTEND}
  $<TARGET_OBJECTS:runtime_end>
  )

target_link_libraries(${PROJECT_NAME}
  gcc
  )

set_target_properties(${PROJECT_NAME}
  PROPERTIES LINK_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/kernel/kernel.ld"
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
