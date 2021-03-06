#ifndef JESSY_MULTIBOOT_TAGS_TAG_HPP
#define JESSY_MULTIBOOT_TAGS_TAG_HPP

#include "multiboot/tags/types.hpp"

#include <cstdint>

namespace os::multiboot::tags
{

  template<type Type = type::unknown>
  struct alignas(8) tag
  {
    static auto constexpr tag_type = Type;
  };

  struct tag_header
  {
    tags::type const type{};
    std::uint32_t const size{};
  };

#define MULTIBOOT_TAG_CLASS_BEGIN(TagType)                                                                                     \
  class TagType : public tag<type::TagType>                                                                                    \
  {                                                                                                                            \
    tag_header const m_header{};

#define MULTIBOOT_TAG_CLASS_END                                                                                                \
  }                                                                                                                            \
  ;
}  // namespace os::multiboot::tags

#endif
