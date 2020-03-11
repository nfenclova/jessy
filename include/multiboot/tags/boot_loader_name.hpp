#ifndef JESSY_MULTIBOOT_TAGS_BOOT_LOADER_NAME_HPP
#define JESSY_MULTIBOOT_TAGS_BOOT_LOADER_NAME_HPP

#include "multiboot/tags/tag.hpp"
#include "multiboot/tags/types.hpp"

namespace os::multiboot::tags
{

  MULTIBOOT_TAG_CLASS_BEGIN(boot_loader_name)
  char const m_name{};

public:
  char const * name() const noexcept
  {
    return &m_name;
  }
  MULTIBOOT_TAG_CLASS_END

}  // namespace os::multiboot::tags

#endif
