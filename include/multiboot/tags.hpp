#ifndef JESSY_MULTIBOOT_TAGS_HPP
#define JESSY_MULTIBOOT_TAGS_HPP

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
    image_load_base_address
    };

  struct alignas(8) tag { };

  struct boot_command_line : tag
    {
    static auto constexpr type = tags::type::boot_command_line;

    operator char const * () const;

    private:
      char const data{};
    };

  struct boot_loader_name : tag
    {
    static auto constexpr type = tags::type::boot_loader_name;

    operator char const * () const;

    private:
      char const data{};
    };

  struct module : tag
    {
    static auto constexpr type = tags::type::module;

    os::core::uint32_t const start_address;
    os::core::uint32_t const end_address;
    os::core::uint8_t const * const string;
    };

  struct basic_memory_information : tag
    {
    static auto constexpr type = tags::type::basic_memory_information;

    os::core::uint32_t const lower_memory;
    os::core::uint32_t const upper_memory;
    };

  struct efi32_image_handle_pointer : tag
    {
    static auto constexpr type = tags::type::efi32_image_handle_pointer;

    os::core::uint32_t const lower_memory;
    os::core::uint32_t const upper_memory;
    };

  }

#endif
