#ifndef JESSY_MULTIBOOT_TAGS_ELF_SYMBOLS_HPP
#define JESSY_MULTIBOOT_TAGS_ELF_SYMBOLS_HPP

#include "multiboot/tags/tag.hpp"
#include "multiboot/tags/types.hpp"
#include "core/error.hpp"

namespace os::multiboot::tags
  {

  MULTIBOOT_TAG_CLASS_BEGIN(elf_symbols)
    iso::uint32_t const m_count{};
    iso::uint32_t const m_entrySize{};
    iso::uint32_t const m_sectionHeaderIndex{};
    char const m_data{};

    public:
      enum struct section_type : iso::uint32_t
        {
        unused,
        program_data,
        symbol_table,
        string_table,
        relocation_entries_with_addends,
        symbol_hash_table,
        dynamic_linking_information,
        notes,
        program_space_without_data,
        relocation_entries_no_addends,
        reserved,
        dynamic_linker_symbol_table,
        array_of_constructors,
        array_of_destructors,
        array_of_pre_constructors,
        section_group,
        extended_section_indices,
        number_of_defined_types,
        };

      enum struct section_flags : iso::uint64_t
        {
        writable = 0x1,
        allocated = 0x2,
        executable = 0x4,
        mergeable = 0x10,
        strings = 0x20,
        sht_index = 0x40,
        preserve_order = 0x80,
        os_specific_handling_required = 0x100,
        is_group_member = 0x200,
        thread_local_data = 0x400,
        os_specific = 0x0ff00000,
        processor_specific = 0xf0000000,
        ordering_required = 0x4000000,
        excluded = 0x8000000,
        };

      class entry
        {
        iso::uint32_t const m_nameOffset{};
        section_type const m_type{};
        section_flags const m_flags{};
        void const* m_virtualAddress{};
        iso::uint64_t const m_offset{};
        iso::uint64_t const m_size{};
        iso::uint32_t const m_link{};
        iso::uint32_t const m_info{};
        iso::uint64_t const m_alignment{};
        iso::uint64_t const m_entrySize{};

        public:
          section_type const & type() const noexcept { return m_type; }
          section_flags const & flags() const noexcept { return m_flags; }
          void const * const & address() const noexcept { return m_virtualAddress; }
          uint64_t const & size() const noexcept { return m_size; }

        friend elf_symbols;
        };

      iso::uint32_t const & count() const noexcept { return m_count; }
      iso::uint32_t const & entry_size() const noexcept { return m_entrySize; }

      entry const * begin() const { return reinterpret_cast<entry const *>(&m_data); }
      entry const * end() const { return begin() + count(); }

      char const * name(entry const & entry) const noexcept
        {
        auto const stringTableNode = begin() + m_sectionHeaderIndex;
        auto const stringTable = reinterpret_cast<char const *>(stringTableNode->address());
        return stringTable + entry.m_nameOffset;
        }
  MULTIBOOT_TAG_CLASS_END

  char const * to_string(elf_symbols::section_type type)
    {
#define CASE(Enumerator) case elf_symbols::section_type::Enumerator: return #Enumerator;
    switch(type)
      {
      CASE(unused)
      CASE(program_data)
      CASE(symbol_table)
      CASE(string_table)
      CASE(relocation_entries_with_addends)
      CASE(symbol_hash_table)
      CASE(dynamic_linking_information)
      CASE(notes)
      CASE(program_space_without_data)
      CASE(relocation_entries_no_addends)
      CASE(reserved)
      CASE(dynamic_linker_symbol_table)
      CASE(array_of_constructors)
      CASE(array_of_destructors)
      CASE(array_of_pre_constructors)
      CASE(section_group)
      CASE(extended_section_indices)
      CASE(number_of_defined_types)
      }
#undef CASE

    core::panic("Unhandled Multiboot 2 ELF section type");
    }

  constexpr bool operator&(elf_symbols::section_flags const & lhs, elf_symbols::section_flags const & rhs)
    {
    return static_cast<iso::uint64_t>(lhs) & static_cast<iso::uint64_t>(rhs);
    }

  }

#endif
