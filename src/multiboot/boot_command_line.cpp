#include "multiboot/tags.hpp"

namespace os::multiboot::tags
  {

  boot_command_line::operator char const * () const
    {
    return &data;
    }

  }
