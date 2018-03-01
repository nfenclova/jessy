#include "core/error.hpp"
#include "core/int_types.hpp"
#include "vga/text.hpp"
#include "bootstrap/addresses.hpp"

#include "multiboot/information.hpp"

extern "C" void _init();

constexpr auto cDefaultOutputColor = os::vga::text::color{
  os::vga::text::foreground_color::green,
  os::vga::text::foreground_modifier::bright,
  os::vga::text::background_color::black,
  os::vga::text::background_modifier::none
};

namespace
  {
  void print_memory_info()
    {
    using os::vga::text::print, os::vga::text::print_line;
    using namespace os::bootstrap;

    print(cDefaultOutputColor, "[PHYSM] ");
    print(cDefaultOutputColor, cPhysicalMemoryStartAddress);
    print(cDefaultOutputColor, " - ");
    print(cDefaultOutputColor, cPhysicalMemoryEndAddress);

    print_line(cDefaultOutputColor, "");

    print(cDefaultOutputColor, "[VIRTM] ");
    print(cDefaultOutputColor, cVirtualMemoryStartAddress);
    print(cDefaultOutputColor, " - ");
    print(cDefaultOutputColor, cVirtualMemoryEndAddress);

    print_line(cDefaultOutputColor, "");
    }

  void print_bootloader_info(os::multiboot::information const * info)
    {
    using os::vga::text::print, os::vga::text::print_line;

    if(info->has<os::multiboot::tags::boot_loader_name>())
      {
      print(cDefaultOutputColor, "[BOOTI] Loaded by: ");
      print_line(cDefaultOutputColor, info->get<os::multiboot::tags::boot_loader_name>());
      }

    if(info->has<os::multiboot::tags::boot_command_line>())
      {
      print(cDefaultOutputColor, "[BOOTI] Using command args: ");
      print_line(cDefaultOutputColor, info->get<os::multiboot::tags::boot_command_line>());
      }
    }
  }

extern "C" void kernel_main(os::multiboot::information const * multiboot_information)
  {
  using os::vga::text::print_line;

  print_line(cDefaultOutputColor, "[JESSY] Entered kernel_main");

  print_bootloader_info(multiboot_information);

  print_memory_info();

  _init();

  os::core::panic({__func__, __FILE__}, "Control-flow returned from kernel!");
  }
