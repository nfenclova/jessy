#ifndef KERNEL_VGA_HPP
#define KERNEL_VGA_HPP

#include "core/int_types.hpp"

namespace os
  {

  enum struct vga_foreground_color : os::core::byte_t
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

  enum struct vga_foreground_modifier : os::core::byte_t
    {
    none,
    bright = 0b00001000,
    };

  enum struct vga_background_color : os::core::byte_t
    {
    black = static_cast<unsigned char>(vga_foreground_color::black) << 4,
    blue = static_cast<unsigned char>(vga_foreground_color::blue) << 4,
    green = static_cast<unsigned char>(vga_foreground_color::green) << 4,
    cyan = static_cast<unsigned char>(vga_foreground_color::cyan) << 4,
    red = static_cast<unsigned char>(vga_foreground_color::red) << 4,
    magenta = static_cast<unsigned char>(vga_foreground_color::magenta) << 4,
    brown = static_cast<unsigned char>(vga_foreground_color::brown) << 4,
    gray = static_cast<unsigned char>(vga_foreground_color::gray) << 4,
    };

  enum struct vga_background_modifier : os::core::byte_t
    {
    none,
    blink = 0b10000000,
    };

  struct vga_color
    {
    vga_foreground_color foreground_color;
    vga_foreground_modifier foreground_modifier;
    vga_background_color background_color;
    vga_background_modifier vga_background_modifier;

    constexpr operator os::core::uint16_t() const
      {
      return (
        static_cast<uint16_t>(foreground_color)        |
        static_cast<uint16_t>(foreground_modifier)     |
        static_cast<uint16_t>(background_color)        |
        static_cast<uint16_t>(vga_background_modifier)
      ) << 8;
      }
    };

  inline decltype(auto) vga_text_buffer(os::core::ptrdiff_t offset)
    {
    return (*reinterpret_cast<uint16_t volatile *>(0xb8000 + offset * 2));
    }

  void print(os::vga_color color, char const * const text)
    {
    for(auto idx = 0ull; text[idx]; ++idx)
      {
      os::vga_text_buffer(idx) = color + text[idx];
      }
    }

  }

#endif
