#include "core/error.hpp"
#include "core/int_types.hpp"
#include "vga/text.hpp"
#include "bootstrap/addresses.hpp"

extern "C" void _init();

constexpr auto cDefaultOutputColor = os::vga::text::color{
  os::vga::text::foreground_color::green,
  os::vga::text::foreground_modifier::bright,
  os::vga::text::background_color::black,
  os::vga::text::background_modifier::none
};

extern "C" void kernel_main()
  {
  os::vga::text::print_line(cDefaultOutputColor, "[JESSY] Entered kernel_main");

  os::vga::text::print(cDefaultOutputColor, "[PHYSM] ");
  os::vga::text::print(cDefaultOutputColor, os::bootstrap::cPhysicalMemoryStartAddress);
  os::vga::text::print(cDefaultOutputColor, " - ");
  os::vga::text::print(cDefaultOutputColor, os::bootstrap::cPhysicalMemoryEndAddress);

  os::vga::text::print_line(cDefaultOutputColor, "");

  os::vga::text::print(cDefaultOutputColor, "[VIRTM] ");
  os::vga::text::print(cDefaultOutputColor, os::bootstrap::cVirtualMemoryStartAddress);
  os::vga::text::print(cDefaultOutputColor, " - ");
  os::vga::text::print(cDefaultOutputColor, os::bootstrap::cVirtualMemoryEndAddress);

  os::vga::text::print_line(cDefaultOutputColor, "");

  _init();

  os::core::panic({__func__, __FILE__}, "Control-flow returned from kernel!");
  }
