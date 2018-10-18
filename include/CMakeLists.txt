# vim: ft=cmake ts=2 sw=2 et

include_directories("${CMAKE_CURRENT_SOURCE_DIR}")

add_library(headers INTERFACE)
target_include_directories(headers INTERFACE
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
  $<INSTALL_INTERFACE:include/${PROJECT_NAME}>
)