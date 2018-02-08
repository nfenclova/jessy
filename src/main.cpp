#include "core/int_types.hpp"
#include "vga/text.hpp"

extern "C" void kernel_main()
  {
  os::vga::text::print({
    os::vga::text::foreground_color::green,
    os::vga::text::foreground_modifier::bright,
    os::vga::text::background_color::black,
    os::vga::text::background_modifier::none},
    "Booted to C++-land"
  );
  }
