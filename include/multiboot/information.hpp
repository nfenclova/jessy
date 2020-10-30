#ifndef JESSY_MULTIBOOT_INFORMATION_HPP
#define JESSY_MULTIBOOT_INFORMATION_HPP

#include "multiboot/tags.hpp"

#include <cstdint>

namespace os::multiboot
{

  template<typename... Handlers>
  struct tag_visitor : Handlers...
  {
    template<typename T>
    void operator()(T const &) const
    {
    }

    using Handlers::operator()...;
  };

  template<typename... Handlers>
  tag_visitor(Handlers...) -> tag_visitor<Handlers...>;

  struct information
  {
    information() = delete;

    template<typename... Handlers>
    void accept(tag_visitor<Handlers...> && visitor) const
    {
      auto tag = reinterpret_cast<tags::tag_header const *>(this + 1);
      while (tag->type != tags::type::end)
      {
        switch (tag->type)
        {
#define CASE(Type)                                                                                                             \
  case tags::Type::tag_type:                                                                                                   \
    visitor(reinterpret_cast<tags::Type const &>(*tag));                                                                       \
    break;
          CASE(boot_command_line)
          CASE(boot_loader_name)
          CASE(basic_memory_information)
          CASE(boot_device)
          CASE(memory_map)
          CASE(framebuffer_information)
          CASE(elf_symbols)
#undef CASE
        default:
          visitor(tags::tag{});
        }
        tag += (tag->size + sizeof(tags::tag_header) - 1) / sizeof(tags::tag_header);
      }
    }

  private:
    std::uint32_t total_size;
    std::uint32_t reserved;
  };

}  // namespace os::multiboot

#endif
