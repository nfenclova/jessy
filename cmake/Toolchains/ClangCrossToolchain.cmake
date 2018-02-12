# vim: ft=cmake ts=2 sw=2 et

if(NOT X86_64_ELF_GCC)
  set(CROSS_GCC_PREFIX
    "x86_64-elf-"
    )
  find_program(X86_64_ELF_GCC
    "${CROSS_GCC_PREFIX}gcc"
    DOC "Path to ${CROSS_GCC_PREFIX}gcc"
    )
  if(NOT X86_64_ELF_GCC)
    message(FATAL_ERROR
      "Unable to find x86_64-elf-gcc installation"
      )
  else()
    message(STATUS
      "Found GCC cross compiler: ${X86_64_ELF_GCC}"
      )
    mark_as_advanced(X86_64_ELF_GCC)
  endif()

  find_program(CMAKE_OBJDUMP
    "${CROSS_GCC_PREFIX}objdump"
    DOC "Path to ${CROSS_GCC_PREFIX}objdump"
    )

  find_program(CMAKE_OBJCOPY
    "${CROSS_GCC_PREFIX}objcopy"
    DOC "Path to ${CROSS_GCC_PREFIX}objcopy"
    )

  find_program(CMAKE_NM
    "${CROSS_GCC_PREFIX}nm"
    DOC "Path to ${CROSS_GCC_PREFIX}nm"
    )

  find_program(CMAKE_CXX_COMPILER_RANLIB
    "${CROSS_GCC_PREFIX}ranlib"
    DOC "Path to ${CROSS_GCC_PREFIX}ranlib"
    )

  find_program(CMAKE_STRIP
    "${CROSS_GCC_PREFIX}strip"
    DOC "Path to ${CROSS_GCC_PREFIX}strip"
    )

  find_program(CMAKE_LINKER
    "${CROSS_GCC_PREFIX}ld"
    DOC "Path to ${CROSS_GCC_PREFIX}ld"
    )

  find_program(CMAKE_CXX_COMPILER_AR
    "${CROSS_GCC_PREFIX}ar"
    DOC "Path to ${CROSS_GCC_PREFIX}ar"
    )

  execute_process(COMMAND ${X86_64_ELF_GCC} --version
    COMMAND grep -Po \\d\\.\\d\\.\\d
    OUTPUT_VARIABLE CROSS_GCC_VERSION
    ERROR_QUIET
    )

  string(STRIP
    ${CROSS_GCC_VERSION}
    CROSS_GCC_VERSION
    )

  set(CROSS_GCC_VERSION
    ${CROSS_GCC_VERSION}
    CACHE STRING
    ""
    FORCE
    )
  mark_as_advanced(CROSS_GCC_VERSION)
  message(STATUS "Found x86_64-elf cross GCC ${CROSS_GCC_VERSION}")

  execute_process(COMMAND ${X86_64_ELF_GCC} -print-file-name=crtbegin.o
    OUTPUT_VARIABLE CRTBEGIN_OBJECT
    ERROR_QUIET
    )
  string(STRIP ${CRTBEGIN_OBJECT} CRTBEGIN_OBJECT)

  execute_process(COMMAND ${X86_64_ELF_GCC} -print-file-name=crtend.o
    OUTPUT_VARIABLE CRTEND_OBJECT
    ERROR_QUIET
    )
  string(STRIP ${CRTEND_OBJECT} CRTEND_OBJECT)

  set(CMAKE_SYSROOT
    "/usr/lib/gcc/x86_64-elf/${CROSS_GCC_VERSION}"
    CACHE STRING
    ""
    FORCE
    )
  mark_as_advanced(CMAKE_SYSROOT)

  set(CROSS_GCC_CRTBEGIN
    ${CRTBEGIN_OBJECT}
    CACHE FILEPATH
    ""
    FORCE
    )
  mark_as_advanced(CROSS_GCC_CRTBEGIN)

  set(CROSS_GCC_CRTEND
    ${CRTEND_OBJECT}
    CACHE FILEPATH ""
    FORCE
    )
  mark_as_advanced(CROSS_GCC_CRTEND)
endif()

set(CMAKE_SYSTEM_NAME
  "Generic"
  )
set(CMAKE_SYSTEM_PROCESSOR
  "x86_64"
  )

set(CMAKE_CXX_FLAGS_INIT
  "-ffreestanding -nostdlib -static -m64 -mno-red-zone -ffunction-sections -fdata-sections -fno-rtti -fno-exceptions"
  )

find_program(CMAKE_CXX_COMPILER
  "clang++"
  )

set(CMAKE_CXX_COMPILER_TARGET
  "x86_64-none-none-elf"
  )

set(CMAKE_C_SIZEOF_DATA_PTR
  "8"
  CACHE STRING
  ""
  FORCE
  )
mark_as_advanced(CMAKE_C_SIZEOF_DATA_PTR)

set(CMAKE_EXE_LINKER_FLAGS
  "-Wl,-n,--gc-sections,--build-id=none"
  CACHE STRING
  ""
  FORCE
  )
