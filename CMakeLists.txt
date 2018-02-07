cmake_minimum_required(VERSION 3.10.0)
project(kernel
  LANGUAGES C CXX ASM_NASM
  )

find_program(GRUB_MKRESCUE grub-mkrescue)
if(NOT GRUB_MKRESCUE)
  message(FATAL_ERROR "Missing required tool: grub-mkrescue")
endif()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wextra -pedantic")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -T ${CMAKE_CURRENT_SOURCE_DIR}/src/kernel.ld")

set(CMAKE_CXX_STANDARD "17")
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(MAKE_DIRECTORY "${CMAKE_BINARY_DIR}/iso/boot/grub")

add_executable(${PROJECT_NAME}
  "src/boot.asm"
  "src/main.cpp"
  )

set_target_properties(${PROJECT_NAME} PROPERTIES LINK_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/src/kernel.ld)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:${PROJECT_NAME}> "${CMAKE_BINARY_DIR}/iso/boot"
  COMMENT "Copying kernel image..."
  )

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy "${PROJECT_SOURCE_DIR}/support/grub/grub.cfg" "${CMAKE_BINARY_DIR}/iso/boot/grub"
  COMMENT "Copying GRUB configuration ..."
  )

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
  COMMAND ${GRUB_MKRESCUE}
  ARGS -o ${PROJECT_NAME}.iso ${CMAKE_BINARY_DIR}/iso
  COMMENT "Packing bootable ISO..."
  )
