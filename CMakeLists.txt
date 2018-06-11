# vim: ft=cmake ts=2 sw=2 et

# Basic Project Configuration
cmake_minimum_required(VERSION 3.10.0)
project(jessy
  LANGUAGES CXX ASM_NASM
  VERSION 0.1.0
  )

# Add the project local cmake module directory to the search path
list(APPEND
  CMAKE_MODULE_PATH
  "${CMAKE_SOURCE_DIR}/cmake/Modules"
  "${CMAKE_SOURCE_DIR}/cmake/Configuration"
  )

# Apply Project Specific Tool Configurations
include("CXXConfiguration")
include("LinkerConfiguration")
include("NasmConfiguration")

if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang" OR "${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
  add_definitions("-DUNREACHABLE=__builtin_unreachable")
  add_definitions("-DUNDERLYING_TYPE=__underlying_type")
  add_definitions("-DIS_UNION=__is_union")
endif()

include_directories("include")

add_subdirectory("src")
add_subdirectory("support")
