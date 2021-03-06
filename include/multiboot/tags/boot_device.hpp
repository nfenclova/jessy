#ifndef JESSY_MULTIBOOT_TAGS_BOOT_DEVICE_HPP
#define JESSY_MULTIBOOT_TAGS_BOOT_DEVICE_HPP

#include "multiboot/tags/tag.hpp"
#include "multiboot/tags/types.hpp"

#include <cstdint>

namespace os::multiboot::tags
{

  MULTIBOOT_TAG_CLASS_BEGIN(boot_device)
  std::uint32_t const m_biosDevice{};
  std::uint32_t const m_partition{};
  std::uint32_t const m_subPartition{};

public:
  std::uint32_t const & bios_device() const noexcept
  {
    return m_biosDevice;
  }
  std::uint32_t const & partition() const noexcept
  {
    return m_partition;
  }
  std::uint32_t const & sub_partition() const noexcept
  {
    return m_subPartition;
  }
  MULTIBOOT_TAG_CLASS_END

}  // namespace os::multiboot::tags

#endif
