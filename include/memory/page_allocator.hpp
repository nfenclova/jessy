#ifndef JESSY_MEMORY_PAGE_ALLOCATOR_HPP
#define JESSY_MEMORY_PAGE_ALLOCATOR_HPP

#include "iso/optional.hpp"
#include "memory/page.hpp"
#include "units/bytes.hpp"

namespace os::memory::page_allocator
  {

  iso::optional<page> alloc(os::units::bytes size);

  }

#endif
