# vim: ft=cmake ts=2 sw=2 et

set(ISOFS_DIRECTORY
  "${CMAKE_CURRENT_BINARY_DIR}/isofs"
  )

file(MAKE_DIRECTORY
  "${ISOFS_DIRECTORY}/boot/grub"
  )

configure_file("${CMAKE_CURRENT_SOURCE_DIR}/grub/grub.cfg"
  "${ISOFS_DIRECTORY}/boot/grub/grub.cfg"
  )

add_custom_command(OUTPUT "${ISOFS_DIRECTORY}/boot/${PROJECT_NAME}"
  COMMAND ${CMAKE_COMMAND}
  ARGS -E copy "$<TARGET_FILE:${PROJECT_NAME}>" "${ISOFS_DIRECTORY}/boot"
  DEPENDS ${PROJECT_NAME}
  )

add_custom_command(OUTPUT "${CMAKE_CURRENT_BINARY_DIR}/boot.iso"
  COMMAND ${GRUB_MKRESCUE} 2>/dev/null
  ARGS -o "${CMAKE_CURRENT_BINARY_DIR}/boot.iso" "${ISOFS_DIRECTORY}"
  DEPENDS "${ISOFS_DIRECTORY}/boot/${PROJECT_NAME}" "${ISOFS_DIRECTORY}/boot/grub/grub.cfg"
  )

add_custom_target(iso
  ALL
  SOURCES "${CMAKE_CURRENT_BINARY_DIR}/boot.iso"
  )

add_custom_target(boot
  COMMAND "${PROJECT_SOURCE_DIR}/support/tools/run.sh"
  DEPENDS iso
  )

add_custom_target(boot_debug
  COMMAND "${PROJECT_SOURCE_DIR}/support/tools/debug.sh"
  DEPENDS ${CMAKE_BINARY_DIR}/debug_info.sym iso
  )
