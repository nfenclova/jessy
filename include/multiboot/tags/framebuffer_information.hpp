#ifndef JESSY_MULTIBOOT_TAGS_FRAMEBUFFER_INFORMATION_HPP
#define JESSY_MULTIBOOT_TAGS_FRAMEBUFFER_INFORMATION_HPP

#include "multiboot/tags/tag.hpp"
#include "multiboot/tags/types.hpp"

namespace os::multiboot::tags
  {

  MULTIBOOT_TAG_CLASS_BEGIN(framebuffer_information)
    core::uint64_t const m_address{};
    core::uint32_t const m_pitch{};
    core::uint32_t const m_width{};
    core::uint32_t const m_height{};
    core::uint8_t const m_bitsPerPixel{};
    core::uint8_t const m_type{};
    core::uint8_t const m_reserved{};
    core::uint8_t const m_data{};

    public:
      enum struct framebuffer_type : core::uint8_t
        {
        indexed,
        rgb,
        ega_text,
        };

      class indexed_color_information
        {
        core::uint32_t const m_numberOfColors{};
        core::uint8_t const m_data{};

        public:
          struct entry
            {
            core::uint8_t const red{};
            core::uint8_t const green{};
            core::uint8_t const blue{};
            };

          core::uint32_t const & number_of_colors() const noexcept { return m_numberOfColors; }
        };

      class rgb_color_information
        {
        core::uint8_t const m_redFieldPosition{};
        core::uint8_t const m_redMaskSize{};
        core::uint8_t const m_greenFieldPosition{};
        core::uint8_t const m_greenMaskSize{};
        core::uint8_t const m_blueFieldPosition{};
        core::uint8_t const m_blueMaskSize{};

        public:
          core::uint8_t const & red_field_position() const noexcept { return m_redFieldPosition; }
          core::uint8_t const & red_mask_size() const noexcept { return m_redMaskSize; }
          core::uint8_t const & green_field_position() const noexcept { return m_greenFieldPosition; }
          core::uint8_t const & green_mask_size() const noexcept { return m_greenMaskSize; }
          core::uint8_t const & blue_field_position() const noexcept { return m_blueFieldPosition; }
          core::uint8_t const & blue_mask_size() const noexcept { return m_blueMaskSize; }
        };

      core::uint64_t const & address() const noexcept { return m_address; }
      core::uint32_t const & pitch() const noexcept { return m_pitch; }
      core::uint32_t const & width() const noexcept { return m_width; }
      core::uint32_t const & height() const noexcept { return m_height; }
      core::uint8_t const & bit_per_pixel() const noexcept { return m_bitsPerPixel; }
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
    }

  }

#endif
