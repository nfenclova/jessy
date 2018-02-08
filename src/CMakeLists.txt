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
  COMMAND "objcopy"
  ARGS --only-keep-debug "$<TARGET_FILE:${PROJECT_NAME}>" ${CMAKE_BINARY_DIR}/${PROJECT_NAME}.sym
  COMMENT "Extracting debug info..."
  )

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
  COMMAND "objcopy"
  ARGS --strip-debug "$<TARGET_FILE:${PROJECT_NAME}>"
  COMMENT "Stripping debug info from kernel image..."
  )

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
  COMMAND ${CMAKE_COMMAND}
  ARGS -E copy "$<TARGET_FILE:${PROJECT_NAME}>" "${CMAKE_BINARY_DIR}/iso/boot"
  COMMENT "Copying kernel image..."
  )

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
  COMMAND ${CMAKE_COMMAND}
  ARGS -E copy "${PROJECT_SOURCE_DIR}/support/grub/grub.cfg" "${CMAKE_BINARY_DIR}/iso/boot/grub"
  COMMENT "Copying GRUB configuration ..."
  )

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
  COMMAND ${GRUB_MKRESCUE}
  ARGS -o "${CMAKE_BINARY_DIR}/${PROJECT_NAME}.iso" "${CMAKE_BINARY_DIR}/iso"
  COMMENT "Packing bootable ISO..."
  )
