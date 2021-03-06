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
  LANGUAGES CXX ASM
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

### Include Jessy C++ Standard Library
FetchContent_Declare("cpplib"
  GIT_REPOSITORY "https://github.com/nfenclova/jessy-cpplib.git"
  GIT_TAG "master"
)
FetchContent_MakeAvailable("cpplib")


### Kernel Executable
add_executable("${PROJECT_NAME}"
  # Bootstrap
  "src/bootstrap/boot.s"
  "src/bootstrap/multiboot_header.s"
  "src/bootstrap/transition.s"

  # Core
  "src/core/error.cpp"
  "src/core/memory.s"

  # Kernel
  "src/kernel/main.cpp"

  # Memory
  "src/memory/page_allocator.cpp"
  "src/memory/page.cpp"

  # VGA
  "src/vga/text.cpp"
)

set_target_properties("${PROJECT_NAME}" PROPERTIES
  CXX_STANDARD "20"
  CXX_EXTENSIONS OFF
  CXX_STANDARD_REQUIRED YES
  INTERPROCEDURAL_OPTIMIZATION ${ENABLE_LTO}
  LINK_DEPENDS "${PROJECT_SOURCE_DIR}/scripts/jessy.ld"
  ADDITIONAL_CLEAN_FILES "${DEBUG_SYMBOL_FILE}"
)

target_compile_options("${PROJECT_NAME}" PUBLIC
  "-Wall"
  "-Wextra"
  "-Werror"
  "-pedantic-errors"
  "-ggdb3"
  "-gdwarf"
  "-Wa,-I${PROJECT_SOURCE_DIR}/include"
)

target_compile_definitions("${PROJECT_NAME}" PRIVATE
  "UNREACHABLE=__builtin_unreachable"
  "UNDERLYING_TYPE=__underlying_type"
)

target_include_directories("${PROJECT_NAME}" PRIVATE
  "${PROJECT_SOURCE_DIR}/include"
)

target_link_directories("${PROJECT_NAME}" PRIVATE "scripts")
target_link_options("${PROJECT_NAME}" PUBLIC "-Tjessy.ld")
target_link_libraries("${PROJECT_NAME}" PRIVATE
  "gcc"
  "jessy::c++"
)
jessy_link_runtime("${PROJECT_NAME}")

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