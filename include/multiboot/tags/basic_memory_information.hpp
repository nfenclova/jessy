#ifndef JESSY_MULTIBOOT_TAGS_BASIC_MEMORY_INFORMATION_HPP
#define JESSY_MULTIBOOT_TAGS_BASIC_MEMORY_INFORMATION_HPP

#include "multiboot/tags/tag.hpp"
#include "multiboot/tags/types.hpp"

namespace os::multiboot::tags
  {

  MULTIBOOT_TAG_CLASS_BEGIN(basic_memory_information)
    core::uint32_t const m_lowerMemory{};
    core::uint32_t const m_upperMemory{};

    public:
      core::uint32_t const & lower_memory() const noexcept { return m_lowerMemory; }
      core::uint32_t const & upper_memory() const noexcept { return m_upperMemory; }
  MULTIBOOT_TAG_CLASS_END

  }

#endif
