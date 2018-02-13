# vim: ft=cmake ts=2 sw=2 et

include("FindPackageHandleStandardArgs")

set(PROGRAM_NAME
  "qemu-system-x86_64"
  )
set(OUTVAR
  "QEMU_SYSTEM_X86_64"
  )

find_program(${OUTVAR}
  "${PROGRAM_NAME}"
  )
if(NOT ${OUTVAR})
  message(FATAL_ERROR "Missing required tool: ${PROGRAM_NAME}")
endif()

find_package_handle_standard_args(${PROGRAM_NAME} DEFAULT_MSG
  ${OUTVAR}
  )
