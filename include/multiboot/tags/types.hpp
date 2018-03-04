#ifndef JESSY_MULTIBOOT_TAGS_TYPES_HPP
#define JESSY_MULTIBOOT_TAGS_TYPES_HPP

#include "core/int_types.hpp"

namespace os::multiboot::tags
  {

  enum struct type : os::core::uint32_t
    {
    end,
    boot_command_line,
    boot_loader_name,
    module,
    basic_memory_information,
    boot_device,
    memory_map,
    vbe_information,
    framebuffer_information,
    elf_symbols,
    apm_table,
    efi32_system_table_pointer,
    efi64_system_table_pointer,
    smbios_table,
    acpi_old_rsdp,
    acpi_new_rsdp,
    networking_information,
    efi_memory_map,
    efi_boot_services_not_terminated,
    efi32_image_handle_pointer,
    efi64_image_handle_pointer,
    image_load_base_address,
    unknown,
    };

  }

#endif
