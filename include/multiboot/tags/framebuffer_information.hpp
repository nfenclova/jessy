#ifndef JESSY_MULTIBOOT_TAGS_FRAMEBUFFER_INFORMATION_HPP
#define JESSY_MULTIBOOT_TAGS_FRAMEBUFFER_INFORMATION_HPP

#include "multiboot/tags/tag.hpp"
#include "multiboot/tags/types.hpp"
#include "core/error.hpp"

namespace os::multiboot::tags
  {

  MULTIBOOT_TAG_CLASS_BEGIN(framebuffer_information)
    iso::uint64_t const m_address{};
    iso::uint32_t const m_pitch{};
    iso::uint32_t const m_width{};
    iso::uint32_t const m_height{};
    iso::uint8_t const m_bitsPerPixel{};
    iso::uint8_t const m_type{};
    iso::uint8_t const m_reserved{};
    iso::uint8_t const m_data{};

    public:
      enum struct framebuffer_type : iso::uint8_t
        {
        indexed,
        rgb,
        ega_text,
        };

      class indexed_color_information
        {
        iso::uint32_t const m_numberOfColors{};
        iso::uint8_t const m_data{};

        public:
          struct entry
            {
            iso::uint8_t const red{};
            iso::uint8_t const green{};
            iso::uint8_t const blue{};
            };

          iso::uint32_t const & number_of_colors() const noexcept { return m_numberOfColors; }
        };

      class rgb_color_information
        {
        iso::uint8_t const m_redFieldPosition{};
        iso::uint8_t const m_redMaskSize{};
        iso::uint8_t const m_greenFieldPosition{};
        iso::uint8_t const m_greenMaskSize{};
        iso::uint8_t const m_blueFieldPosition{};
        iso::uint8_t const m_blueMaskSize{};

        public:
          iso::uint8_t const & red_field_position() const noexcept { return m_redFieldPosition; }
          iso::uint8_t const & red_mask_size() const noexcept { return m_redMaskSize; }
          iso::uint8_t const & green_field_position() const noexcept { return m_greenFieldPosition; }
          iso::uint8_t const & green_mask_size() const noexcept { return m_greenMaskSize; }
          iso::uint8_t const & blue_field_position() const noexcept { return m_blueFieldPosition; }
          iso::uint8_t const & blue_mask_size() const noexcept { return m_blueMaskSize; }
        };

      iso::uint64_t const & address() const noexcept { return m_address; }
      iso::uint32_t const & pitch() const noexcept { return m_pitch; }
      iso::uint32_t const & width() const noexcept { return m_width; }
      iso::uint32_t const & height() const noexcept { return m_height; }
      iso::uint8_t const & bit_per_pixel() const noexcept { return m_bitsPerPixel; }
      framebuffer_type const & type() const noexcept { return *reinterpret_cast<framebuffer_type const *>(&m_type); }
  MULTIBOOT_TAG_CLASS_END

  char const * to_string(framebuffer_information::framebuffer_type type)
    {
#define CASE(Enumerator) case framebuffer_information::framebuffer_type::Enumerator: return #Enumerator;
    switch(type)
      {
      CASE(indexed)
      CASE(rgb)
      CASE(ega_text)
      }
#undef CASE

    core::panic(iso::source_location::current(), "Unhandled Multiboot 2 framebuffer type");
    }

  }

#endif
