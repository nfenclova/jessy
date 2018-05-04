#ifndef JESSY_MULTIBOOT_TAGS_MEMORY_MAP_HPP
#define JESSY_MULTIBOOT_TAGS_MEMORY_MAP_HPP

#include "multiboot/tags/tag.hpp"
#include "multiboot/tags/types.hpp"
#include "core/error.hpp"

namespace os::multiboot::tags
  {

  MULTIBOOT_TAG_CLASS_BEGIN(memory_map)
    iso::uint32_t const m_entrySize{};
    iso::uint32_t const m_entryVersion{};

    public:
      enum struct entry_type : iso::uint32_t
        {
        available = 1,
        reserved = 2,
        acpi_reclaimable = 3,
        nvs = 4,
        bad_ram = 5,
        };

      struct entry
        {
        void const * const & base_address() const noexcept { return m_baseAddress; }
        iso::uint64_t const & length() const noexcept { return m_length; }
        entry_type const & type() const noexcept { return m_type; }

        private:
          void const * const m_baseAddress{};
          iso::uint64_t const m_length{};
          entry_type const m_type{};
          iso::uint32_t const m_reserved{};
        };

      iso::uint32_t const & entry_size() const noexcept { return m_entrySize; }
      iso::uint32_t const & entry_version() const noexcept { return m_entryVersion; }
      iso::uint32_t entries() const noexcept { return (m_header.size - sizeof(memory_map)) / m_entrySize; }
      entry const * begin() const noexcept { return reinterpret_cast<entry const *>(this + 1); }
      entry const * end() const noexcept { return begin() + entries(); }
  MULTIBOOT_TAG_CLASS_END

  char const * to_string(memory_map::entry_type type)
    {
#define CASE(Enumerator) case memory_map::entry_type::Enumerator: return #Enumerator;
    switch(type)
      {
      CASE(available)
      CASE(reserved)
      CASE(acpi_reclaimable)
      CASE(nvs)
      CASE(bad_ram)
      }
#undef CASE

    core::panic(iso::source_location::current(), "Unhandled Multiboot 2 memory map type");
    }

  }

#endif
