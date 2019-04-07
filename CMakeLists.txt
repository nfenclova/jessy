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

if(NOT CMAKE_EXPORT_COMPILE_COMMANDS)
  set(CMAKE_EXPORT_COMPILE_COMMANDS ON CACHE BOOL "" FORCE)
endif()

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

add_library("includes" INTERFACE)
target_include_directories("includes" INTERFACE
  $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
  $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/src/bootstrap>
  $<INSTALL_INTERFACE:include/${PROJECT_NAME}>
)

add_executable(${PROJECT_NAME}
  # Runtime (init)
  "src/runtime/crti.asm"
  "${CROSS_GCC_CRTBEGIN}"

  # Bootstrap
  "src/bootstrap/boot.asm"
  "src/bootstrap/multiboot_header.asm"
  "src/bootstrap/transition.asm"

  # Core
  "src/core/error.cpp"
  "src/core/memory.asm"

  # Kernel
  "src/kernel/main.cpp"

  # Memory
  "src/memory/page_allocator.cpp"
  "src/memory/page.cpp"

  # VGA
  "src/vga/text.cpp"

  # Runtime (end)
  "${CROSS_GCC_CRTEND}"
  "src/runtime/crtn.asm"
)

set_target_properties(${PROJECT_NAME}
  PROPERTIES LINK_DEPENDS "${PROJECT_SOURCE_DIR}/src/kernel/kernel.ld"
  )
target_link_libraries(${PROJECT_NAME}
  "gcc"
  "includes"
)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
  COMMAND "${CMAKE_OBJCOPY}"
  ARGS --only-keep-debug "$<TARGET_FILE:${PROJECT_NAME}>" "${DEBUG_SYMBOL_FILE}"
  BYPRODUCTS "${DEBUG_SYMBOL_FILE}"
  )
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
  COMMAND "${CMAKE_STRIP}"
  ARGS --strip-debug "$<TARGET_FILE:${PROJECT_NAME}>"
  )
set_directory_properties(PROPERTY ADDITIONAL_MAKE_CLEAN_FILES
  "${DEBUG_SYMBOL_FILE}"
  )

add_subdirectory("support")
