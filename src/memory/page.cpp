#include "memory/page.hpp"

#include <cstddef>
#include <cstdint>

namespace os::memory
{

  page::operator void *() const
  {
    return reinterpret_cast<void *>(id * static_cast<std::size_t>(cPageSize));
  }

  page page::for_address(void const * address)
  {
    return page{reinterpret_cast<std::uintptr_t>(address) / static_cast<std::uint64_t>(cPageSize)};
  }

}  // namespace os::memory
