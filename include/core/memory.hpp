#ifndef JESSY_CORE_MEMORY_HPP
#define JESSY_CORE_MEMORY_HPP

#include "core/int_types.hpp"

extern "C" void _set_memory_byte(os::core::uint8_t volatile *, os::core::uint8_t const, size_t);
extern "C" void _set_memory_word(os::core::uint16_t volatile *, os::core::uint16_t const, size_t);
extern "C" void _set_memory_double_word(os::core::uint32_t volatile *, os::core::uint32_t const, size_t const);
extern "C" void _set_memory_quad_word(os::core::uint64_t volatile *, os::core::uint64_t const, size_t const);

extern "C" void _copy_memory_byte(os::core::uint8_t volatile *, os::core::uint8_t volatile const *, size_t);
extern "C" void _copy_memory_word(os::core::uint16_t volatile *, os::core::uint16_t volatile const *, size_t);
extern "C" void _copy_memory_double_word(os::core::uint32_t volatile *, os::core::uint32_t volatile const *, size_t const count);
extern "C" void _copy_memory_quad_word(os::core::uint64_t volatile *, os::core::uint64_t volatile const *, size_t const count);

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
      static_assert(sizeof(ValueType) == 8, "Can only copy 1, 2, 4, or 8 byte values");
      _set_memory_quad_word(reinterpret_cast<uint64_t volatile *>(destination), static_cast<uint64_t>(value), count);
      }
    }

  /**
   * @brief Copy @p count values of type @p ValueType from the memory pointed to by @p source to @p destination
   *
   * @param destination  The target memory location
   * @param source       The source memory location
   * @param count        The number of values to copy from @p source to @destination
   *
   * @since 0.1.0
   * @author Natalia Fenclová
   */
  template<typename ValueType>
  void copy_memory(ValueType volatile * destination, ValueType volatile const * source, size_t count)
    {
    if constexpr(sizeof(ValueType) == 1)
      {
      _copy_memory_byte(reinterpret_cast<uint8_t volatile *>(destination),
                        reinterpret_cast<uint8_t volatile const *>(source),
                        count);
      }
    else if constexpr(sizeof(ValueType) == 2)
      {
      _copy_memory_word(reinterpret_cast<uint16_t volatile *>(destination),
                        reinterpret_cast<uint16_t volatile const *>(source),
                        count);
      }
    else if constexpr(sizeof(ValueType) == 4)
      {
      _copy_memory_double_word(reinterpret_cast<uint32_t volatile *>(destination),
                               reinterpret_cast<uint32_t volatile const *>(source),
                               count);
      }
    else
      {
      static_assert(sizeof(ValueType) == 8, "Can only copy 1, 2, 4, or 8 byte values");
      _copy_memory_quad_word(reinterpret_cast<uint64_t volatile *>(destination),
                             reinterpret_cast<uint64_t volatile const *>(source),
                             count);
      }
    }
  }

#endif
