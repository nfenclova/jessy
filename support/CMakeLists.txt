# vim: ft=cmake ts=2 sw=2 et

include("FindExternalTool")

find_external_tool(NAME GRUB_MKRESCUE COMMAND "grub-mkrescue" REQUIRED)
find_external_tool(NAME QEMU COMMAND "qemu-system-x86_64" REQUIRED)
find_external_tool(NAME GDB COMMAND "gdb" REQUIRED)

set(ISOFS_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/isofs")
set(ISO_FILE "${CMAKE_CURRENT_BINARY_DIR}/boot.iso")
set(SYMBOL_FILE "${CMAKE_BINARY_DIR}/debug_info.sym")

file(MAKE_DIRECTORY "${ISOFS_DIRECTORY}/boot/grub")

configure_file("${CMAKE_CURRENT_SOURCE_DIR}/grub/grub.cfg"
  "${ISOFS_DIRECTORY}/boot/grub/grub.cfg"
  )

add_custom_command(OUTPUT "${ISOFS_DIRECTORY}/boot/${PROJECT_NAME}"
  COMMAND ${CMAKE_COMMAND}
  ARGS -E copy "$<TARGET_FILE:${PROJECT_NAME}>" "${ISOFS_DIRECTORY}/boot"
  DEPENDS ${PROJECT_NAME}
  )

add_custom_command(OUTPUT "${CMAKE_CURRENT_BINARY_DIR}/boot.iso"
  COMMAND ${GRUB_MKRESCUE_EXE} 2>/dev/null
  ARGS -o "${ISO_FILE}" "${ISOFS_DIRECTORY}"
  DEPENDS "${ISOFS_DIRECTORY}/boot/${PROJECT_NAME}" "${ISOFS_DIRECTORY}/boot/grub/grub.cfg"
  )

add_custom_target(iso ALL
  SOURCES "${ISO_FILE}"
  )

add_custom_target(boot
  COMMAND ${QEMU_EXE} -cdrom ${ISO_FILE} 2>/dev/null
  DEPENDS iso
  )

add_custom_target(boot_debug
  COMMAND ${QEMU_EXE} -S -s -cdrom ${ISO_FILE} 2>/dev/null &
  COMMAND ${GDB_EXE} -s "${SYMBOL_FILE}" -q -ex "target remote localhost:1234" -ex "break _start" -ex "c"
  DEPENDS ${SYMBOL_FILE} iso
  )

add_custom_target(disassemble
  COMMAND ${CMAKE_OBJDUMP} -d -Mintel -C "$<TARGET_FILE:${PROJECT_NAME}>"
  DEPENDS ${PROJECT_NAME}
  )
