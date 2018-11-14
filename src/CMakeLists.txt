# vim: ft=cmake ts=2 sw=2 et

set(GENERATED_FILES)

add_subdirectory("bootstrap")
add_subdirectory("core")
add_subdirectory("kernel")
add_subdirectory("memory")
add_subdirectory("runtime")
add_subdirectory("vga")

add_executable(${PROJECT_NAME}
  $<TARGET_OBJECTS:runtime_init>
  ${CROSS_GCC_CRTBEGIN}

  $<TARGET_OBJECTS:bootstrap>
  $<TARGET_OBJECTS:core>
  $<TARGET_OBJECTS:kernel>
  $<TARGET_OBJECTS:memory>
  $<TARGET_OBJECTS:vga>

  ${CROSS_GCC_CRTEND}
  $<TARGET_OBJECTS:runtime_end>
  )

target_link_libraries(${PROJECT_NAME}
  gcc
  headers
  )

set_target_properties(${PROJECT_NAME}
  PROPERTIES LINK_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/kernel/kernel.ld"
  )

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
  COMMAND "${CMAKE_OBJCOPY}"
  ARGS --only-keep-debug "$<TARGET_FILE:${PROJECT_NAME}>" "${DEBUG_SYMBOL_FILE}"
  BYPRODUCTS "${DEBUG_SYMBOL_FILE}"
  )
list(APPEND GENERATED_FILES
  "${DEBUG_SYMBOL_FILE}"
  )

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
  COMMAND "${CMAKE_STRIP}"
  ARGS --strip-debug "$<TARGET_FILE:${PROJECT_NAME}>"
  )

set_directory_properties(PROPERTY ADDITIONAL_MAKE_CLEAN_FILES
  "${GENERATED_FILES}"
  )
