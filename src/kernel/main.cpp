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
    print_line(cDefaultOutputColor, cPhysicalMemoryEndAddress);

    print(cDefaultOutputColor, "[VIRTM] ");
    print(cDefaultOutputColor, cVirtualMemoryStartAddress);
    print(cDefaultOutputColor, " - ");
    print_line(cDefaultOutputColor, cVirtualMemoryEndAddress);
    }

  void print_multiboot_information(os::multiboot::information const * info)
    {
    using os::vga::text::print, os::vga::text::print_line;

    info->accept(os::multiboot::tag_visitor{
      [](os::multiboot::tags::boot_loader_name const & tag) {
        print(cDefaultOutputColor, "[MBOOT] Loaded by: ");
        print_line(cDefaultOutputColor, tag.name());
      },
      [](os::multiboot::tags::boot_command_line const & tag) {
        print(cDefaultOutputColor, "[MBOOT] Using command args: ");
        print_line(cDefaultOutputColor, tag.command_line());
      },
      [](os::multiboot::tags::basic_memory_information const & tag) {
        print_line(cDefaultOutputColor, "[MBOOT] Memory information:");
        print(cDefaultOutputColor, "    Lower memory: ");
        print(cDefaultOutputColor, tag.lower_memory());
        print_line(cDefaultOutputColor, " kB");
        print(cDefaultOutputColor, "    Upper memory: ");
        print(cDefaultOutputColor, tag.upper_memory());
        print_line(cDefaultOutputColor, " kB");
      },
      [](os::multiboot::tags::boot_device const & tag) {
        print_line(cDefaultOutputColor, "[MBOOT] BIOS boot device: ");
        print(cDefaultOutputColor, "    device number:");
        print_line(cDefaultOutputColor, tag.bios_device());
        print(cDefaultOutputColor, "    partition number: ");
        print_line(cDefaultOutputColor, tag.partition());
        print(cDefaultOutputColor, "    sub-partition number: ");
        print_line(cDefaultOutputColor, tag.sub_partition());
      },
      [](os::multiboot::tags::memory_map const & tag) {
        print_line(cDefaultOutputColor, "[MBOOT] Available memory:");
        for(auto const & entry : tag)
          {
          if(entry.type() == os::multiboot::tags::memory_map::entry_type::available)
            {
            print(cDefaultOutputColor, "    ");
            print(cDefaultOutputColor, entry.base_address());
            print(cDefaultOutputColor, " - ");
            print(cDefaultOutputColor, entry.length());
            print_line(cDefaultOutputColor, " bytes");
            }
          }
      },
      [](os::multiboot::tags::framebuffer_information const & tag) {
        print_line(cDefaultOutputColor, "[MBOOT] Framebuffer information:");
        print(cDefaultOutputColor, "    type: ");
        print_line(cDefaultOutputColor, to_string(tag.type()));
        switch(tag.type())
          {
          case os::multiboot::tags::framebuffer_information::framebuffer_type::ega_text:
            print(cDefaultOutputColor, "    dimensions: ");
            print(cDefaultOutputColor, tag.width());
            print(cDefaultOutputColor, "x");
            print(cDefaultOutputColor, tag.height());
            print_line(cDefaultOutputColor, " characters");
            break;
          default:
            break;
          }
      },
      [](os::multiboot::tags::elf_symbols const & tag) {
        print_line(cDefaultOutputColor, "[MBOOT] Executable sections:");
        for(auto const & entry : tag)
          {
          if(entry.flags() & os::multiboot::tags::elf_symbols::section_flags::executable)
            {
            print(cDefaultOutputColor, "    ");
            print(cDefaultOutputColor, tag.name(entry));
            print(cDefaultOutputColor, ": ");
            print(cDefaultOutputColor, entry.address());
            print(cDefaultOutputColor, " - ");
            print(cDefaultOutputColor, entry.size());
            print_line(cDefaultOutputColor, " bytes");
            }
          }
      },
    });
    }
  }

extern "C" void kernel_main(os::multiboot::information const * multiboot_information)
  {
  using os::vga::text::print_line;

  print_line(cDefaultOutputColor, "[JESSY] Entered kernel_main");

  print_multiboot_information(multiboot_information);

  print_memory_info();

  _init();

  os::core::panic(os::core::source_location::current(), "Control-flow returned from kernel!");
  }
