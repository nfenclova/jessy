#ifndef JESSY_UNITS_BYTES_HPP
#define JESSY_UNITS_BYTES_HPP

#include "core/strong_type.hpp"
#include "iso/cstdint.hpp"

namespace os::units
{

  struct bytes_strong_tag
  {
  };
  using bytes = core::strong_type<iso::uint64_t, bytes_strong_tag>;

  constexpr bytes operator""_byte(unsigned long long const size) noexcept
  {
    return bytes{size};
  }

  constexpr bytes operator""_kibi_byte(unsigned long long const size) noexcept
  {
    return bytes{size << 10};
  }

  constexpr bytes operator""_mebi_byte(unsigned long long const size) noexcept
  {
    return bytes{size << 20};
  }

  constexpr bytes operator""_gibi_byte(unsigned long long const size) noexcept
  {
    return bytes{size << 30};
  }

}  // namespace os::units

#endif
