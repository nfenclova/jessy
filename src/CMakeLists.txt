add_executable(${PROJECT_NAME}
  "boot.asm"
  "main.cpp"
  )

set_target_properties(${PROJECT_NAME}
  PROPERTIES LINK_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/kernel.ld"
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
