#ifndef KERNEL_VGA_TEXT_HPP
#define KERNEL_VGA_TEXT_HPP

#include "core/int_types.hpp"

namespace os::vga::text
  {

  enum struct foreground_color : os::core::byte_t
    {
    black,
    blue,
    green,
    cyan,
    red,
    magenta,
    brown,
    gray,
    };

  enum struct foreground_modifier : os::core::byte_t
    {
    none,
    bright = 0b00001000,
    };

  enum struct background_color : os::core::byte_t
    {
    black = static_cast<unsigned char>(foreground_color::black) << 4,
    blue = static_cast<unsigned char>(foreground_color::blue) << 4,
    green = static_cast<unsigned char>(foreground_color::green) << 4,
    cyan = static_cast<unsigned char>(foreground_color::cyan) << 4,
    red = static_cast<unsigned char>(foreground_color::red) << 4,
    magenta = static_cast<unsigned char>(foreground_color::magenta) << 4,
    brown = static_cast<unsigned char>(foreground_color::brown) << 4,
    gray = static_cast<unsigned char>(foreground_color::gray) << 4,
    };

  enum struct background_modifier : os::core::byte_t
    {
    none,
    blink = 0b10000000,
    };

  struct color
    {
    explicit constexpr operator os::core::uint16_t() const
      {
      return (
        static_cast<uint16_t>(foreground_color)        |
        static_cast<uint16_t>(foreground_modifier)     |
        static_cast<uint16_t>(background_color)        |
        static_cast<uint16_t>(background_modifier)
      ) << 8;
      }

    foreground_color foreground_color;
    foreground_modifier foreground_modifier;
    background_color background_color;
    background_modifier background_modifier;
    };

  uint16_t volatile & buffer();

  void print(color color, char const * const text);

  void clear_screen();

  }

#endif
