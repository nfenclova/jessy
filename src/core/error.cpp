#include "core/error.hpp"
#include "vga/text.hpp"

namespace os::core
  {

  /**
   * Internal constants
   */
  namespace
    {
    auto constexpr cPanicOutputColor = vga::text::color{
      vga::text::foreground_color::red,
      vga::text::foreground_modifier::bright,
      vga::text::background_color::blue,
      vga::text::background_modifier::none,
    };
    }

  [[noreturn]]
  void panic(panic_location const location, char const * const message)
    {
    vga::text::print(cPanicOutputColor, "!!!PANIC!!! @ ");
    vga::text::print(cPanicOutputColor, location.function);
    vga::text::print(cPanicOutputColor, ":");
    vga::text::print(cPanicOutputColor, location.file);
    vga::text::print(cPanicOutputColor, ": ");
    vga::text::print(cPanicOutputColor, message);

    __asm__ volatile ( "hlt" );
    __builtin_unreachable();
    }

  }
