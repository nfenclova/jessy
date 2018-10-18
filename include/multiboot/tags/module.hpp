#ifndef JESSY_MULTIBOOT_TAGS_MODULE_HPP
#define JESSY_MULTIBOOT_TAGS_MODULE_HPP

#include "multiboot/tags/tag.hpp"
#include "multiboot/tags/types.hpp"

namespace os::multiboot::tags
  {

  MULTIBOOT_TAG_CLASS_BEGIN(module)
    iso::uint32_t const m_startAddress{};
    iso::uint32_t const m_endAddress{};
    char const m_string{};

    public:
      iso::uint32_t const & start_address() const noexcept { return m_startAddress; }
      iso::uint32_t const & end_address() const noexcept { return m_endAddress; }
      char const * string() const noexcept { return & m_string; }
  MULTIBOOT_TAG_CLASS_END


  }

#endif
