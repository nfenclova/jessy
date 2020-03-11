#ifndef JESSY_MEMORY_PAGE_HPP
#define JESSY_MEMORY_PAGE_HPP

#include "iso/cstddef.hpp"
#include "iso/cstdint.hpp"
#include "units/bytes.hpp"

namespace os::memory
{

  constexpr units::bytes cPageSize{4'096};

  struct page
  {
    static page for_address(void const * address);

    operator void *() const;
    iso::size_t const id{};
  };

}  // namespace os::memory

#endif
