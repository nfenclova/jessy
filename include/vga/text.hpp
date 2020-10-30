#ifndef JESSY_VGA_TEXT_HPP
#define JESSY_VGA_TEXT_HPP

#include "iso/type_traits.hpp"

#include <cstddef>
#include <cstdint>

namespace os::vga::text
{

  enum struct foreground_color : iso::underlying_type_t<std::byte>
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

  enum struct foreground_modifier : iso::underlying_type_t<std::byte>
  {
    none,
    bright = 0b00001000,
  };

  enum struct background_color : iso::underlying_type_t<std::byte>
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

  enum struct background_modifier : iso::underlying_type_t<std::byte>
  {
    none,
    blink = 0b10000000,
  };

  struct color
  {
    explicit constexpr operator std::uint16_t() const
    {
      return static_cast<std::uint16_t>(static_cast<std::byte>(foreground_color) | static_cast<std::byte>(foreground_modifier) |
                                        static_cast<std::byte>(background_color) | static_cast<std::byte>(background_modifier))
             << 8;
    }

    os::vga::text::foreground_color foreground_color;
    os::vga::text::foreground_modifier foreground_modifier;
    os::vga::text::background_color background_color;
    os::vga::text::background_modifier background_modifier;
  };

  void print(color color, char const * const text);

  void print(color color, void const * const pointer);

  void print(color color, std::uint32_t value);

  void print_line(color color, char const * const text);

  void print_line(color color, void const * const pointer);

  void print_line(color color, std::uint32_t const value);

  void clear_screen();

}  // namespace os::vga::text

#endif
