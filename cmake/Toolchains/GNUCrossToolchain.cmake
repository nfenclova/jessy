# vim: ft=cmake ts=2 sw=2 et

if(NOT CMAKE_CXX_COMPILER)
  set(CROSS_GCC_PREFIX "x86_64-elf-")
  find_program(CMAKE_OBJDUMP "${CROSS_GCC_PREFIX}objdump" DOC "Path to ${CROSS_GCC_PREFIX}objdump")
  find_program(CMAKE_OBJCOPY "${CROSS_GCC_PREFIX}objcopy" DOC "Path to ${CROSS_GCC_PREFIX}objcopy")
  find_program(CMAKE_NM "${CROSS_GCC_PREFIX}nm" DOC "Path to ${CROSS_GCC_PREFIX}nm")
  find_program(CMAKE_CXX_COMPILER_RANLIB "${CROSS_GCC_PREFIX}ranlib" DOC "Path to ${CROSS_GCC_PREFIX}ranlib")
  find_program(CMAKE_STRIP "${CROSS_GCC_PREFIX}strip" DOC "Path to ${CROSS_GCC_PREFIX}strip")
  find_program(CMAKE_LINKER "${CROSS_GCC_PREFIX}ld" DOC "Path to ${CROSS_GCC_PREFIX}ld")
  find_program(CMAKE_CXX_COMPILER_AR "${CROSS_GCC_PREFIX}ar" DOC "Path to ${CROSS_GCC_PREFIX}ar")
  find_program(CMAKE_CXX_COMPILER "${CROSS_GCC_PREFIX}g++" DOC "Path to ${CROSS_GCC_PREFIX}g++")

  execute_process(COMMAND ${CMAKE_CXX_COMPILER} -print-file-name=crtbegin.o
    OUTPUT_VARIABLE CROSS_GCC_CRTBEGIN
    ERROR_QUIET
    )
  string(STRIP ${CROSS_GCC_CRTBEGIN} CROSS_GCC_CRTBEGIN)
  mark_as_advanced(CROSS_GCC_CRTBEGIN)

  execute_process(COMMAND ${CMAKE_CXX_COMPILER} -print-file-name=crtend.o
    OUTPUT_VARIABLE CROSS_GCC_CRTEND
    ERROR_QUIET
    )
  string(STRIP ${CROSS_GCC_CRTEND} CROSS_GCC_CRTEND)
  mark_as_advanced(CROSS_GCC_CRTEND)

  set(CROSS_GCC_CRTBEGIN ${CROSS_GCC_CRTBEGIN} CACHE STRING "" FORCE)
  set(CROSS_GCC_CRTEND ${CROSS_GCC_CRTEND} CACHE STRING "" FORCE)

  string(REGEX REPLACE "/crtbegin.o" "" CMAKE_SYSROOT ${CROSS_GCC_CRTBEGIN})
  mark_as_advanced(CMAKE_SYSROOT)
  set(CMAKE_SYSROOT ${CMAKE_SYSROOT} CACHE STRING "" FORCE)

  set_property(GLOBAL PROPERTY TARGET_SUPPORTS_SHARED_LIBS TRUE)

  set(CMAKE_SYSTEM_NAME "Generic")
  set(CMAKE_SYSTEM_PROCESSOR "x86_64")
  set(CMAKE_CXX_COMPILER_TARGET "x86_64-none-none-elf")
  set(CMAKE_EXE_LINKER_FLAGS "-Wl,-n,--gc-sections,--build-id=none" CACHE STRING "" FORCE)
  set(CMAKE_CXX_FLAGS_INIT
    "-ffreestanding"
    "-nostdlib"
    "-m64"
    "-mno-red-zone"
    "-mcmodel=large"
    "-ffunction-sections"
    "-fdata-sections"
    "-fno-rtti"
    "-fno-exceptions"
    )
  string(REPLACE ";" " " CMAKE_CXX_FLAGS_INIT "${CMAKE_CXX_FLAGS_INIT}")

  set(CMAKE_C_SIZEOF_DATA_PTR "8" CACHE STRING "" FORCE)
  mark_as_advanced(CMAKE_C_SIZEOF_DATA_PTR)
endif()
