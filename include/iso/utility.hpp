#ifndef JESSY_ISO_UTILITY_HPP
#define JESSY_ISO_UTILITY_HPP

#include "iso/type_traits.hpp"

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

  }

#endif
