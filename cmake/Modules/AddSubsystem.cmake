macro(add_subsystem NAME)
  add_library(${NAME} OBJECT
    ${ARGN}
    )
  target_link_libraries(${NAME} headers)
endmacro()