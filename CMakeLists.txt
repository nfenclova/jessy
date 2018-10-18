# vim: ft=cmake ts=2 sw=2 et

# Set the default toolchain
if(NOT CMAKE_TOOLCHAIN_FILE)
  set(CMAKE_TOOLCHAIN_FILE "${CMAKE_SOURCE_DIR}/cmake/Toolchains/GNUCrossToolchain.cmake")
endif()

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

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE "RelWithDebInfo" CACHE STRING "Choose the type of the build" FORCE)
endif()

if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang" OR "${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
  add_definitions("-DUNREACHABLE=__builtin_unreachable")
  add_definitions("-DUNDERLYING_TYPE=__underlying_type")
endif()

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_ARCHIVE_OUTPUT_DIRECTORY}")

set(ISO_SOURCE_DIRECTORY "${PROJECT_BINARY_DIR}/isofs")
set(ISO_OUTPUT_FILE "${PROJECT_BINARY_DIR}/${PROJECT_NAME}.iso")
set(DEBUG_SYMBOL_FILE "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${PROJECT_NAME}.sym")

add_subdirectory("include")
add_subdirectory("src")
add_subdirectory("support")
