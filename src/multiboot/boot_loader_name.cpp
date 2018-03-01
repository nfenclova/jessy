#include "multiboot/tags.hpp"

namespace os::multiboot::tags
  {

  boot_loader_name::operator char const * () const
    {
    return &data;
    }

  }
