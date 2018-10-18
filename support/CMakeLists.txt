# vim: ft=cmake ts=2 sw=2 et

include("FindExternalTool")

set(QEMU_SYSTEM_MEMORY "128M" CACHE STRING "The ammount RAM presented to the virtual machine")
message(STATUS "QEMU will expose ${QEMU_SYSTEM_MEMORY} of RAM to the virtual machine")

set(GENERATED_FILES)

find_external_tool(NAME GRUB_MKRESCUE COMMAND "grub-mkrescue" REQUIRED)
find_external_tool(NAME QEMU COMMAND "qemu-system-x86_64" REQUIRED)
find_external_tool(NAME GDB COMMAND "gdb" REQUIRED)

file(MAKE_DIRECTORY "${ISO_SOURCE_DIRECTORY}/boot/grub")

configure_file("${CMAKE_CURRENT_SOURCE_DIR}/grub/grub.cfg"
  "${ISO_SOURCE_DIRECTORY}/boot/grub/grub.cfg"
  )

add_custom_command(OUTPUT
  "${ISO_SOURCE_DIRECTORY}/boot/${PROJECT_NAME}"
  "${ISO_SOURCE_DIRECTORY}/boot/${PROJECT_NAME}.sym"
  COMMAND ${CMAKE_COMMAND}
  ARGS -E copy "$<TARGET_FILE:${PROJECT_NAME}>" "${ISO_SOURCE_DIRECTORY}/boot/${PROJECT_NAME}"
  COMMAND ${CMAKE_COMMAND}
  ARGS -E copy "${DEBUG_SYMBOL_FILE}" "${ISO_SOURCE_DIRECTORY}/boot/${PROJECT_NAME}.sym"
  DEPENDS ${PROJECT_NAME}
  )
list(APPEND GENERATED_FILES
  "${ISO_SOURCE_DIRECTORY}/boot/${PROJECT_NAME}"
  "${ISO_SOURCE_DIRECTORY}/boot/${PROJECT_NAME}.sym"
  )

add_custom_command(OUTPUT "${ISO_OUTPUT_FILE}"
  COMMAND ${GRUB_MKRESCUE_EXE} 2>/dev/null
  ARGS -o "${ISO_OUTPUT_FILE}" "${ISO_SOURCE_DIRECTORY}"
  DEPENDS "${ISO_SOURCE_DIRECTORY}/boot/${PROJECT_NAME}" "${ISO_SOURCE_DIRECTORY}/boot/grub/grub.cfg"
  )
list(APPEND GENERATED_FILES
  "${ISO_OUTPUT_FILE}"
  )

add_custom_target(iso ALL
  SOURCES "${ISO_OUTPUT_FILE}"
  )

add_custom_target(boot
  COMMAND ${QEMU_EXE} -m ${QEMU_SYSTEM_MEMORY} -cdrom ${ISO_OUTPUT_FILE} 2>/dev/null
  DEPENDS iso
  )

add_custom_target(boot_debug
  COMMAND ${QEMU_EXE} -S -s -m ${QEMU_SYSTEM_MEMORY} -cdrom ${ISO_OUTPUT_FILE} 2>/dev/null &
  COMMAND ${GDB_EXE} -s "${DEBUG_SYMBOL_FILE}" -q -ex "target remote localhost:1234" -ex "break _start" -ex "c"
  DEPENDS ${SYMBOL_FILE} iso
  )

add_custom_target(disassemble
  COMMAND ${CMAKE_OBJDUMP} -d -Mintel -C "$<TARGET_FILE:${PROJECT_NAME}>"
  DEPENDS ${PROJECT_NAME}
  )

set_directory_properties(PROPERTY ADDITIONAL_MAKE_CLEAN_FILES
  "${GENERATED_FILES}"
  )
