#ifndef JESSY_CORE_MEMORY_HPP
#define JESSY_CORE_MEMORY_HPP

#include "core/int_types.hpp"

extern "C" void _set_memory_byte(os::core::uint8_t volatile *, uint8_t const, size_t);
extern "C" void _set_memory_word(os::core::uint16_t volatile *, uint16_t const, size_t);

namespace os::core
  {
  template<typename ValueType>
  void set_memory(ValueType volatile * destination, ValueType const value, size_t count)
    {
    if constexpr(sizeof(ValueType) == 1)
      {
      _set_memory_byte(reinterpret_cast<uint8_t volatile *>(destination), static_cast<uint8_t>(value), count);
      }
    else if constexpr(sizeof(ValueType) == 2)
      {
      _set_memory_word(reinterpret_cast<uint16_t volatile *>(destination), static_cast<uint16_t>(value), count);
      }
    }
  }

#endif
