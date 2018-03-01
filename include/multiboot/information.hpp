#ifndef JESSY_MULTIBOOT_INFORMATION_HPP
#define JESSY_MULTIBOOT_INFORMATION_HPP

#include "core/int_types.hpp"
#include "multiboot/tags.hpp"

namespace os::multiboot
  {

  struct information
    {
    information() = delete;

    /**
     * @brief Check if the Multiboot 2 information structure contains the given tag type
     */
    template<typename TagType>
    bool has() const noexcept
      {
      return has(TagType::type);
      }

    template<typename TagType>
    TagType const & get() const noexcept
      {
      return reinterpret_cast<TagType const &>(get(TagType::type));
      }

    private:
      struct tag_header
        {
        tags::type const type;
        os::core::uint32_t const size;
        };

      bool has(tags::type type) const noexcept;

      tags::tag const * find(tags::type type) const noexcept;

      tags::tag const & get(tags::type type) const noexcept;

      os::core::uint32_t total_size; 
      os::core::uint32_t reserved;
    };

  }

#endif
