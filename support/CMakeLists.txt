# vim: ft=cmake ts=2 sw=2 et

find_package("GrubMkrescue")
find_package("Qemu")
find_package("GDB")

set(ISOFS_DIRECTORY
  "${CMAKE_CURRENT_BINARY_DIR}/isofs"
  )
set(ISO_FILE
  "${CMAKE_CURRENT_BINARY_DIR}/boot.iso"
  )
set(SYMBOL_FILE
  "${CMAKE_BINARY_DIR}/debug_info.sym"
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
  ARGS -o "${ISO_FILE}" "${ISOFS_DIRECTORY}"
  DEPENDS "${ISOFS_DIRECTORY}/boot/${PROJECT_NAME}" "${ISOFS_DIRECTORY}/boot/grub/grub.cfg"
  )

add_custom_target(iso
  ALL
  SOURCES "${ISO_FILE}"
  )

add_custom_target(boot
  COMMAND ${QEMU_SYSTEM_X86_64} -cdrom ${ISO_FILE} 2>/dev/null
  DEPENDS iso
  )

add_custom_target(boot_debug
  COMMAND ${QEMU_SYSTEM_X86_64} -S -s -cdrom ${ISO_FILE} 2>/dev/null &
  COMMAND ${GDB} -s "${SYMBOL_FILE}" -ex "target remote localhost:1234" -ex "break _start" -ex "c"
  DEPENDS ${SYMBOL_FILE} iso
  )

add_custom_target(disassemble
  COMMAND ${CMAKE_OBJDUMP} -d -Mintel -C "$<TARGET_FILE:${PROJECT_NAME}>"
  DEPENDS ${PROJECT_NAME}
  )
