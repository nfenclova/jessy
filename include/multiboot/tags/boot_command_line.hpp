#ifndef JESSY_MULTIBOOT_TAGS_BOOT_COMMAND_LINE_HPP
#define JESSY_MULTIBOOT_TAGS_BOOT_COMMAND_LINE_HPP

#include "multiboot/tags/tag.hpp"
#include "multiboot/tags/types.hpp"

namespace os::multiboot::tags
{

  MULTIBOOT_TAG_CLASS_BEGIN(boot_command_line)
  char const m_commandLine{};

public:
  char const * command_line() const noexcept
  {
    return &m_commandLine;
  }
  MULTIBOOT_TAG_CLASS_END

}  // namespace os::multiboot::tags

#endif
