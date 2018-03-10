#ifndef JESSY_CORE_UTILITY_HPP
#define JESSY_CORE_UTILITY_HPP

#include "core/type_traits.hpp"

namespace os::core
  {

  template<typename Type>
  constexpr remove_reference_t<Type> && move(Type && value) noexcept
    {
    return static_cast<remove_reference_t<Type> &&>(value);
    }

  }

#endif
