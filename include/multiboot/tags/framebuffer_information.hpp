#ifndef JESSY_MULTIBOOT_TAGS_FRAMEBUFFER_INFORMATION_HPP
#define JESSY_MULTIBOOT_TAGS_FRAMEBUFFER_INFORMATION_HPP

#include "core/error.hpp"
#include "multiboot/tags/tag.hpp"
#include "multiboot/tags/types.hpp"

#include <cstdint>

namespace os::multiboot::tags
{

  MULTIBOOT_TAG_CLASS_BEGIN(framebuffer_information)
  std::uint64_t const m_address{};
  std::uint32_t const m_pitch{};
  std::uint32_t const m_width{};
  std::uint32_t const m_height{};
  std::uint8_t const m_bitsPerPixel{};
  std::uint8_t const m_type{};
  std::uint8_t const m_reserved{};
  std::uint8_t const m_data{};

public:
  enum struct framebuffer_type : std::uint8_t
  {
    indexed,
    rgb,
    ega_text,
  };

  class indexed_color_information
  {
    std::uint32_t const m_numberOfColors{};
    std::uint8_t const m_data{};

  public:
    struct entry
    {
      std::uint8_t const red{};
      std::uint8_t const green{};
      std::uint8_t const blue{};
    };

    std::uint32_t const & number_of_colors() const noexcept
    {
      return m_numberOfColors;
    }
  };

  class rgb_color_information
  {
    std::uint8_t const m_redFieldPosition{};
    std::uint8_t const m_redMaskSize{};
    std::uint8_t const m_greenFieldPosition{};
    std::uint8_t const m_greenMaskSize{};
    std::uint8_t const m_blueFieldPosition{};
    std::uint8_t const m_blueMaskSize{};

  public:
    std::uint8_t const & red_field_position() const noexcept
    {
      return m_redFieldPosition;
    }
    std::uint8_t const & red_mask_size() const noexcept
    {
      return m_redMaskSize;
    }
    std::uint8_t const & green_field_position() const noexcept
    {
      return m_greenFieldPosition;
    }
    std::uint8_t const & green_mask_size() const noexcept
    {
      return m_greenMaskSize;
    }
    std::uint8_t const & blue_field_position() const noexcept
    {
      return m_blueFieldPosition;
    }
    std::uint8_t const & blue_mask_size() const noexcept
    {
      return m_blueMaskSize;
    }
  };

  std::uint64_t const & address() const noexcept
  {
    return m_address;
  }
  std::uint32_t const & pitch() const noexcept
  {
    return m_pitch;
  }
  std::uint32_t const & width() const noexcept
  {
    return m_width;
  }
  std::uint32_t const & height() const noexcept
  {
    return m_height;
  }
  std::uint8_t const & bit_per_pixel() const noexcept
  {
    return m_bitsPerPixel;
  }
  framebuffer_type const & type() const noexcept
  {
    return *reinterpret_cast<framebuffer_type const *>(&m_type);
  }
  MULTIBOOT_TAG_CLASS_END

  char const * to_string(framebuffer_information::framebuffer_type type)
  {
#define CASE(Enumerator)                                                                                                       \
  case framebuffer_information::framebuffer_type::Enumerator:                                                                  \
    return #Enumerator;
    switch (type)
    {
      CASE(indexed)
      CASE(rgb)
      CASE(ega_text)
    }
#undef CASE

    core::panic("Unhandled Multiboot 2 framebuffer type");
  }

}  // namespace os::multiboot::tags

#endif
