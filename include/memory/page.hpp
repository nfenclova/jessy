#ifndef JESSY_MEMORY_PAGE_HPP
#define JESSY_MEMORY_PAGE_HPP

#include "units/bytes.hpp"

#include <cstddef>

namespace os::memory
{

  constexpr units::bytes cPageSize{4'096};

  struct page
  {
    static page for_address(void const * address);

    operator void *() const;
    std::size_t const id{};
  };

}  // namespace os::memory

#endif
