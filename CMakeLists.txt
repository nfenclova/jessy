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

include_directories("include")
add_subdirectory("src")
add_subdirectory("support")
