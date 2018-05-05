#ifndef JESSY_MULTIBOOT_TAGS_TYPES_HPP
#define JESSY_MULTIBOOT_TAGS_TYPES_HPP

#include "iso/cstdint.hpp"
#include "core/error.hpp"

namespace os::multiboot::tags
  {

  enum struct type : iso::uint32_t
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

  char const * to_string(type type)
    {
#define CASE(Enumerator) case type::Enumerator: return #Enumerator;
    switch(type)
      {
      CASE(end)
      CASE(boot_command_line)
      CASE(boot_loader_name)
      CASE(module)
      CASE(basic_memory_information)
      CASE(boot_device)
      CASE(memory_map)
      CASE(vbe_information)
      CASE(framebuffer_information)
      CASE(elf_symbols)
      CASE(apm_table)
      CASE(efi32_system_table_pointer)
      CASE(efi64_system_table_pointer)
      CASE(smbios_table)
      CASE(acpi_old_rsdp)
      CASE(acpi_new_rsdp)
      CASE(networking_information)
      CASE(efi_memory_map)
      CASE(efi_boot_services_not_terminated)
      CASE(efi32_image_handle_pointer)
      CASE(efi64_image_handle_pointer)
      CASE(image_load_base_address)
      CASE(unknown)
      }
#undef CASE

    core::panic("Unhandled Multiboot 2 tag type");
    }

  }

#endif
