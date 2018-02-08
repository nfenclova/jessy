#include "core/int_types.hpp"
#include "vga.hpp"

extern "C" void kernel_main()
  {
  os::print({
    os::vga_foreground_color::green,
    os::vga_foreground_modifier::bright,
    os::vga_background_color::black,
    os::vga_background_modifier::none},
    "Booted to C++-land"
  );
  }
