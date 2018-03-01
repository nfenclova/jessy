#include "multiboot/information.hpp"

#include "core/int_types.hpp"
#include "core/error.hpp"

namespace os::multiboot
  {

  tags::tag const * information::find(tags::type type) const noexcept
    {
    auto header = reinterpret_cast<tag_header const *>(this + 1);

    while(header->type != tags::type::end)
      {
      if(header->type == type)
        {
        return reinterpret_cast<tags::tag const *>(header + 1);
        }

      auto const skipWidth = (header->size + sizeof(tag_header) - 1) / sizeof(tag_header);
      header += skipWidth;
      }

    return nullptr;
    }

  bool information::has(tags::type type) const noexcept
    {
    return find(type);
    }

  tags::tag const & information::get(tags::type type) const noexcept
    {
    auto tag = find(type);
    if(tag)
      {
      return reinterpret_cast<tags::tag const &>(*tag);
      }

    os::core::panic({__func__, __FILE__}, "Tried to access non-existant tag!");
    }

  }
