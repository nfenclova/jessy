cmake_minimum_required(VERSION 3.15.0)

### Default Build Type Configuration
set(CMAKE_BUILD_TYPE
  "RelWithDebInfo"
  CACHE
  STRING
  "Choose the type of build, options are: None Debug Release RelWithDebInfo MinSizeRel"
)

### Include Cross Toolchain
include("FetchContent")

FetchContent_Declare("toolchain"
  GIT_REPOSITORY "https://github.com/nfenclova/jessy-cmake-toolchain.git"
  GIT_TAG "master"
)
FetchContent_MakeAvailable("toolchain")

project(jessy
  LANGUAGES CXX ASM_NASM
  VERSION 0.1.0
)

### CMake Module Configuration
list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/Modules")

include("FindExternalTool")

### Project Configuration Options
option(ENABLE_LTO "Enable Link-Time-Optimization" ON)
set(QEMU_SYSTEM_MEMORY "128M" CACHE STRING "The ammount RAM presented to the virtual machine")

message(STATUS "QEMU will expose ${QEMU_SYSTEM_MEMORY} of RAM to the virtual machine")

### Find Required Tools
find_external_tool(NAME GRUB_MKRESCUE COMMAND "grub-mkrescue" REQUIRED)
find_external_tool(NAME QEMU COMMAND "qemu-system-x86_64" REQUIRED)
find_external_tool(NAME GDB COMMAND "gdb" REQUIRED)

### Kernel Executable
add_executable("${PROJECT_NAME}"
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
)

jessy_link_runtime("${PROJECT_NAME}")

set_target_properties("${PROJECT_NAME}" PROPERTIES
  CXX_STANDARD "20"
  CXX_EXTENSIONS OFF
  CXX_STANDARD_REQUIRED YES
  INTERPROCEDURAL_OPTIMIZATION ${ENABLE_LTO}
  LINK_DEPENDS "${PROJECT_SOURCE_DIR}/src/kernel/kernel.ld"
  ADDITIONAL_CLEAN_FILES "${DEBUG_SYMBOL_FILE}"
)

target_compile_options("${PROJECT_NAME}" PUBLIC
  $<$<COMPILE_LANGUAGE:CXX>:-Wall>
  $<$<COMPILE_LANGUAGE:CXX>:-Wextra>
  $<$<COMPILE_LANGUAGE:CXX>:-Werror>
  $<$<COMPILE_LANGUAGE:CXX>:-pedantic-errors>
  $<$<COMPILE_LANGUAGE:CXX>:-ggdb3>
  $<$<COMPILE_LANGUAGE:ASM_NASM>:-gdwarf>
)

target_compile_definitions("${PROJECT_NAME}" PUBLIC
  "UNREACHABLE=__builtin_unreachable"
  "UNDERLYING_TYPE=__underlying_type"
)

target_include_directories("${PROJECT_NAME}" SYSTEM PUBLIC
  $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
  $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/src/bootstrap>
)

target_link_options("${PROJECT_NAME}" PUBLIC
  "-T${CMAKE_CURRENT_SOURCE_DIR}/src/kernel/kernel.ld"
  $<$<BOOL:${ENABLE_LTO}>:-flto>
  "-fuse-ld=bfd"
)

target_link_libraries("${PROJECT_NAME}" PRIVATE
  "gcc"
)

add_custom_command(TARGET "${PROJECT_NAME}" POST_BUILD
  COMMAND "${CMAKE_OBJCOPY}"
  ARGS
  "--only-keep-debug"
  "$<TARGET_FILE:${PROJECT_NAME}>"
  "${PROJECT_BINARY_DIR}/${PROJECT_NAME}.sym"
  BYPRODUCTS "${PROJECT_BINARY_DIR}/${PROJECT_NAME}.sym"
  COMMENT "Extracting debug information"
  )

add_custom_command(TARGET "${PROJECT_NAME}" POST_BUILD
  COMMAND "${CMAKE_STRIP}"
  ARGS
  "--strip-debug"
  "$<TARGET_FILE:${PROJECT_NAME}>"
  COMMENT "Stripping debug information"
)

### ISO Image Target
file(MAKE_DIRECTORY "${PROJECT_BINARY_DIR}/isofs/boot/grub")

add_custom_command(OUTPUT "${PROJECT_BINARY_DIR}/isofs/boot/${PROJECT_NAME}"
  COMMAND "${CMAKE_COMMAND}"
  ARGS
  "-E"
  "copy"
  "$<TARGET_FILE:${PROJECT_NAME}>"
  "${PROJECT_BINARY_DIR}/isofs/boot/${PROJECT_NAME}"
  DEPENDS "${PROJECT_NAME}"
  COMMENT "Copying kernel to isofs"
)

add_custom_command(OUTPUT "${PROJECT_BINARY_DIR}/isofs/boot/grub/grub.cfg"
  COMMAND "${CMAKE_COMMAND}"
  ARGS
  "-D" "SUPPORT_DIR=${PROJECT_SOURCE_DIR}/support"
  "-D" "ISOFS_DIR=${PROJECT_BINARY_DIR}/isofs"
  "-D" "PROJECT_NAME=${PROJECT_NAME}"
  "-D" "PROJECT_VERSION=${PROJECT_VERSION}"
  "-P" "${PROJECT_SOURCE_DIR}/cmake/Scripts/GenerateGrubConfig.cmake"
  DEPENDS "${PROJECT_SOURCE_DIR}/support/grub/grub.cfg"
  COMMENT "Generating grub configuration"
)

add_custom_target("iso"
  COMMAND "${GRUB_MKRESCUE_EXE}"
  "-o"
  "${PROJECT_BINARY_DIR}/${PROJECT_NAME}.iso"
  "${PROJECT_BINARY_DIR}/isofs"
  "2>/dev/null"
  DEPENDS
  "${PROJECT_BINARY_DIR}/isofs/boot/grub/grub.cfg"
  "${PROJECT_BINARY_DIR}/isofs/boot/${PROJECT_NAME}"
  BYPRODUCTS
  "${PROJECT_BINARY_DIR}/${PROJECT_NAME}.iso"
  COMMENT
  "Creating bootable ISO image"
)

### QEMU Boot Targets
add_custom_target("boot"
  "${QEMU_EXE}"
  "-m"
  "${QEMU_SYSTEM_MEMORY}"
  "-cdrom"
  "${PROJECT_BINARY_DIR}/${PROJECT_NAME}.iso"
  "2>/dev/null"
  DEPENDS
  "${PROJECT_BINARY_DIR}/${PROJECT_NAME}.iso"
  COMMENT "Booting the kernel"
)

add_custom_target("boot_debug"
  COMMAND "${QEMU_EXE}"
  "-S"
  "-s"
  "-m"
  "${QEMU_SYSTEM_MEMORY}"
  "-cdrom"
  "${PROJECT_BINARY_DIR}/${PROJECT_NAME}.iso"
  "2>/dev/null"
  "&"
  COMMAND "${GDB_EXE}"
  "-s"
  "${PROJECT_BINARY_DIR}/${PROJECT_NAME}.sym"
  "-q"
  "-ex"
  "target remote localhost:1234"
  "-ex" "break _start"
  "-ex" "c"
  DEPENDS
  "${PROJECT_BINARY_DIR}/${PROJECT_NAME}.iso"
  "${PROJECT_BINARY_DIR}/${PROJECT_NAME}.sym"
  COMMENT "Booting the kernel with gdb attached"
)

### Disassembly Target
add_custom_target("disassemble"
  COMMAND "${CMAKE_OBJDUMP}"
  "-d"
  "-Mintel"
  "-C"
  "$<TARGET_FILE:${PROJECT_NAME}>"
  DEPENDS
  "$<TARGET_FILE:${PROJECT_NAME}>"
  COMMENT "Dumping disassembly of the kernel"
  )