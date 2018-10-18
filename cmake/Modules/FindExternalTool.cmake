# vim: ft=cmake ts=2 sw=2 et

include("FindPackageHandleStandardArgs")
include("CMakeParseArguments")

function(find_external_tool)
  set(OPTIONS REQUIRED)
  set(SINGLE_VALUE_ARGUMENTS NAME COMMAND)
  set(MULTI_VALUE_ARGUMENTS)
  cmake_parse_arguments(FIND_EXTERNAL_TOOL
    "${OPTIONS}"
    "${SINGLE_VALUE_ARGUMENTS}"
    "${MULTI_VALUE_ARGUMENTS}"
    "${ARGN}")

  if(NOT FIND_EXTERNAL_TOOL_NAME)
    message(FATAL_ERROR "Missing argument 'NAME' in call to 'find_external_tool'")
  endif()

  if(NOT FIND_EXTERNAL_TOOL_COMMAND)
    message(FATAL_ERROR "Missing argument 'COMMAND' in call to 'find_external_tool'")
  endif()

  find_program(${FIND_EXTERNAL_TOOL_NAME}_EXE "${FIND_EXTERNAL_TOOL_COMMAND}")

  if(FIND_EXTERNAL_TOO_REQUIRED AND NOT ${FIND_EXTERNAL_TOOL_EXE})
    message(FATAL_ERROR "Missing required tool: ${FIND_EXTERNAL_TOOL_NAME}")
  endif()

  find_package_handle_standard_args(${FIND_EXTERNAL_TOOL_NAME} DEFAULT_MSG
    ${FIND_EXTERNAL_TOOL_NAME}_EXE
    )
  mark_as_advanced(${FIND_EXTERNAL_TOOL_NAME}_EXE)
endfunction()
