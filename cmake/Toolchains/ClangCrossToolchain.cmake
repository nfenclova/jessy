set(CMAKE_SYSTEM_NAME "Generic")
set(CMAKE_SYSTEM_PROCESSOR "x86_64")

set(TRIPLE "x86_64-none-elf")
set(COMPILER_FLAGS "-ffreestanding -nostdlib -static -m64 -mno-red-zone -ffunction-sections -fdata-sections")

if(NOT CROSS_GCC_VERSION)
  message(STATUS "Searching x86_64-elf cross GCC")
  execute_process(COMMAND x86_64-elf-gcc --version
    COMMAND grep -Po \\d\\.\\d\\.\\d
    OUTPUT_VARIABLE CROSS_GCC_VERSION
    ERROR_QUIET
    )

  set(CROSS_GCC_VERSION ${CROSS_GCC_VERSION} CACHE STRING "" FORCE)

  if(NOT CROSS_GCC_VERSION)
    message(FATAL_ERROR "Failed to find x86_64-elf cross GCC!")
  else()
    message(STATUS "Found x86_64-elf cross GCC ${CROSS_GCC_VERSION}")
  endif()

  execute_process(COMMAND x86_64-elf-gcc -print-file-name=crtbegin.o
    OUTPUT_VARIABLE CRTBEGIN_OBJECT
    ERROR_QUIET
    )
  string(STRIP ${CRTBEGIN_OBJECT} CRTBEGIN_OBJECT)

  execute_process(COMMAND x86_64-elf-gcc -print-file-name=crtend.o
    OUTPUT_VARIABLE CRTEND_OBJECT
    ERROR_QUIET
    )
  string(STRIP ${CRTEND_OBJECT} CRTEND_OBJECT)

  set(CROSS_GCC_SYSROOT "/usr/lib/gcc/x86_64-elf/${CROSS_GCC_VERSION}" CACHE STRING "" FORCE)
  set(CROSS_GCC_CRTBEGIN ${CRTBEGIN_OBJECT} CACHE STRING "" FORCE)
  set(CROSS_GCC_CRTEND ${CRTEND_OBJECT} CACHE STRING "" FORCE)
endif()

set(CMAKE_CXX_FLAGS_INIT "${COMPILER_FLAGS} -fno-rtti -fno-exceptions")
set(CMAKE_CXX_COMPILER "clang++")
set(CMAKE_CXX_COMPILER_TARGET "${TRIPLE}")

set(CMAKE_C_SIZEOF_DATA_PTR "8" CACHE STRING "" FORCE)

set(CMAKE_EXE_LINKER_FLAGS "-Wl,-n,--gc-sections,--build-id=none" CACHE STRING "" FORCE)
