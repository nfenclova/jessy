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
    image_load_base_address,
    unknown,
    };

  template<type Type = type::unknown>
  struct alignas(8) tag
    {
    static auto constexpr type = Type;
    };

  struct tag_header
    {
    tags::type const type{};
    core::uint32_t const size{};
    };

  struct boot_command_line : tag<type::boot_command_line>
    {
    char const * command_line() const noexcept { return &m_commandLine; }

    private:
      tag_header const m_header{};
      char const m_commandLine{};
    };

  struct boot_loader_name : tag<type::boot_loader_name>
    {
    char const * name() const noexcept { return &m_name; }

    private:
      tag_header const m_header{};
      char const m_name{};
    };

  struct module : tag<type::module>
    {
    core::uint32_t const & start_address() const noexcept { return m_startAddress; }
    core::uint32_t const & end_address() const noexcept { return m_endAddress; }
    char const * string() const noexcept { return & m_string; } 

    private:
      tag_header const m_header{};
      core::uint32_t const m_startAddress{};
      core::uint32_t const m_endAddress{};
      char const m_string{};
    };

  struct basic_memory_information : tag<type::basic_memory_information>
    {
    core::uint32_t const & lower_memory() const noexcept { return m_lowerMemory; }
    core::uint32_t const & upper_memory() const noexcept { return m_upperMemory; }

    private:
      tag_header const m_header{};
      core::uint32_t const m_lowerMemory{};
      core::uint32_t const m_upperMemory{};
    };

  struct boot_device : tag<type::boot_device>
    {
    core::uint32_t const & bios_device() const noexcept { return m_biosDevice; }
    core::uint32_t const & partition() const noexcept { return m_partition; }
    core::uint32_t const & sub_partition() const noexcept { return m_subPartition; }

    private:
      tag_header const m_header{};
      core::uint32_t const m_biosDevice{};
      core::uint32_t const m_partition{};
      core::uint32_t const m_subPartition{};
    };

  struct memory_map : tag<type::memory_map>
    {
    struct entry
      {
      void const * const & base_address() const noexcept { return m_baseAddress; }
      core::uint64_t const & length() const noexcept { return m_length; }
      core::uint32_t const & type() const noexcept { return m_type; }

      private:
        void const * const m_baseAddress{};
        core::uint64_t const m_length{};
        core::uint32_t const m_type{};
        core::uint32_t const m_reserved{};
      };

    core::uint32_t const & entry_size() const noexcept { return m_entrySize; }
    core::uint32_t const & entry_version() const noexcept { return m_entryVersion; }

    core::uint32_t entries() const noexcept { return (m_header.size - sizeof(memory_map)) / m_entrySize; }

    entry const * begin() const noexcept { return reinterpret_cast<entry const *>(this + 1); }

    entry const * end() const noexcept { return begin() + entries(); }

    private:
      tag_header const m_header{};
      core::uint32_t const m_entrySize{};
      core::uint32_t const m_entryVersion{};
    };

  struct efi32_image_handle_pointer : tag<type::efi32_image_handle_pointer>
    {
    core::uintptr_t pointer() const noexcept { return m_pointer; }

    private:
      tag_header const m_header{};
      core::uint32_t const m_pointer{};
    };

  }

#endif
