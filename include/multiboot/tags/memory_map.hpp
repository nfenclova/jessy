#ifndef JESSY_MULTIBOOT_TAGS_MEMORY_MAP_HPP
#define JESSY_MULTIBOOT_TAGS_MEMORY_MAP_HPP

#include "multiboot/tags/tag.hpp"
#include "multiboot/tags/types.hpp"

namespace os::multiboot::tags
  {

  MULTIBOOT_TAG_CLASS_BEGIN(memory_map)
    core::uint32_t const m_entrySize{};
    core::uint32_t const m_entryVersion{};

    public:
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
  MULTIBOOT_TAG_CLASS_END

  }

#endif
