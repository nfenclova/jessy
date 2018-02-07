set(CMAKE_SYSTEM_NAME "Generic")
set(CMAKE_SYSTEM_PROCESSOR "x86_64")

set(TRIPLE "x86_64-none-elf")
set(COMPILER_FLAGS "-ffreestanding -nostdlib -static -m64")

set(CMAKE_C_FLAGS_INIT "${COMPILER_FLAGS}")
set(CMAKE_C_COMPILER "clang")
set(CMAKE_C_COMPILER_TARGET "${TRIPLE}")

set(CMAKE_CXX_FLAGS_INIT "${COMPILER_FLAGS} -fno-rtti -fno-exceptions")
set(CMAKE_CXX_COMPILER "clang++")
set(CMAKE_CXX_COMPILER_TARGET "${TRIPLE}")

set(CMAKE_C_SIZEOF_DATA_PTR "8" CACHE STRING "" FORCE)
set(CMAKE_EXE_LINKER_FLAGS "-Wl,-n,--gc-sections,--build-id=none" CACHE STRING "" FORCE)
