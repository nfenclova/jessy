#include "memory/page_allocator.hpp"

namespace os::memory::page_allocator
{
  namespace
  {
  }

  iso::optional<page> alloc(units::bytes size)
  {
    (void)size;
    return {};
  }

}  // namespace os::memory::page_allocator