#ifndef JESSY_ISO_UTILITY_HPP
#define JESSY_ISO_UTILITY_HPP

#include "iso/type_traits.hpp"

#include <cstddef>

namespace os::iso
{

  template<typename Type>
  constexpr remove_reference_t<Type> && move(Type && value) noexcept
  {
    return static_cast<remove_reference_t<Type> &&>(value);
  }

  template<typename Type>
  constexpr Type && forward(remove_reference_t<Type> & value) noexcept
  {
    return static_cast<Type &&>(value);
  }

  template<typename Type>
  constexpr Type && forward(remove_reference_t<Type> && value) noexcept
  {
    return static_cast<Type &&>(value);
  }

  struct in_place_t
  {
    explicit in_place_t() = default;
  };

  inline constexpr in_place_t in_place{};

  template<typename Type>
  struct in_place_type_t
  {
    explicit in_place_type_t() = default;
  };

  template<typename Type>
  inline constexpr in_place_type_t<Type> in_place_type{};

  template<std::size_t Index>
  struct in_place_index_t
  {
    explicit in_place_index_t() = default;
  };

  template<std::size_t Index>
  inline constexpr in_place_index_t<Index> in_place_index{};

}  // namespace os::iso

#endif
