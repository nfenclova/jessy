cmake_minimum_required(VERSION 3.10.0)
project(kernel
  LANGUAGES CXX ASM_NASM
  )

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/Modules")

set(CMAKE_ASM_NASM_FLAGS "${CMAKE_ASM_NASM_FLAGS} -gdwarf")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wextra -Werror -pedantic-errors -g3")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -T ${CMAKE_CURRENT_SOURCE_DIR}/src/kernel.ld")

set(CMAKE_CXX_STANDARD "17")
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include("FindGrubMkrescue")

file(MAKE_DIRECTORY "${CMAKE_BINARY_DIR}/iso/boot/grub")

include_directories("include")
add_subdirectory("src")
