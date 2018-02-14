#ifndef JESSY_CORE_MEMORY_HPP
#define JESSY_CORE_MEMORY_HPP

#include "core/int_types.hpp"

extern "C" void _set_memory_byte(os::core::uint8_t volatile *, uint8_t const, size_t);
extern "C" void _set_memory_word(os::core::uint16_t volatile *, uint16_t const, size_t);
extern "C" void _set_memory_double_word(os::core::uint32_t volatile * destination, os::core::uint32_t const value, size_t const count);
extern "C" void _set_memory_quad_word(os::core::uint64_t volatile * destination, os::core::uint64_t const value, size_t const count);

namespace os::core
  {
  /**
   * @brief Initialize the memory pointed to by @p destination with @p count copies of @p value
   *
   * @param destination  The target memory location
   * @param value        The value to copy to the memory pointed to by @p destination
   * @param count        The number of copies of @p value to copy to the memory location pointed to by @p destination
   *
   * @since 0.1.0
   * @author Natalia Fenclová
   */
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
    else if constexpr(sizeof(ValueType) == 4)
      {
      _set_memory_double_word(reinterpret_cast<uint32_t volatile *>(destination), static_cast<uint32_t>(value), count);
      }
    else
      {
      _set_memory_quad_word(reinterpret_cast<uint64_t volatile *>(destination), static_cast<uint64_t>(value), count);
      }
    }
  }

#endif
