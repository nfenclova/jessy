macro(add_module NAME)
  set(${NAME}_OUTPUT_PATH "${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/mod_${NAME}.so")

  file(MAKE_DIRECTORY ${CMAKE_LIBRARY_OUTPUT_DIRECTORY})

  add_library(${NAME} OBJECT
    ${ARGN}
    )

  target_compile_options(${NAME} PRIVATE "-fno-function-sections")
  target_compile_options(${NAME} PRIVATE "-fno-data-sections")

  string(REPLACE " " ";" ${NAME}_LINKER_FLAGS ${CMAKE_CXX_FLAGS})
  list(APPEND ${NAME}_LINKER_FLAGS "-r")
  list(APPEND ${NAME}_LINKER_FLAGS "-shared")

  add_custom_target(mod_${NAME} ALL
    COMMAND ${CMAKE_CXX_COMPILER} ${${NAME}_LINKER_FLAGS} $<TARGET_OBJECTS:${NAME}> -o ${${NAME}_OUTPUT_PATH}
    COMMAND ${CMAKE_STRIP} --strip-debug ${${NAME}_OUTPUT_PATH}
    COMMAND_EXPAND_LISTS
    DEPENDS ${NAME}
    SOURCES $<TARGET_OBJECTS:${NAME}>
    COMMENT "Linking kernel module '${NAME}' (mod_${NAME}.so)"
    )

  set_directory_properties(PROPERTY ADDITIONAL_MAKE_CLEAN_FILES
    "${${NAME}_OUTPUT_PATH}"
    )

  target_link_libraries(${NAME} headers)
endmacro()
