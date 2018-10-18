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
  void panic(char const * const message, iso::source_location const location)
    {
    vga::text::print(cPanicOutputColor, "[PANIC] ");
    vga::text::print(cPanicOutputColor, location.function_name());
    vga::text::print(cPanicOutputColor, ":");
    vga::text::print_line(cPanicOutputColor, location.file_name());
    vga::text::print(cPanicOutputColor, "[PANIC] Error: ");
    vga::text::print(cPanicOutputColor, message);

    __asm__ volatile ( "hlt" );
    UNREACHABLE();
    }

  }
