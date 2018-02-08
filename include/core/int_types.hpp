#ifndef KERNEL_CORE_INT_TYPES_HPP
#define KERNEL_CORE_INT_TYPES_HPP

#include <stdint.h>
#include <stddef.h>

namespace os::core
  {

  using ::int8_t;
  using ::int16_t;
  using ::int32_t;
  using ::int64_t;

  using ::int_fast8_t;
  using ::int_fast16_t;
  using ::int_fast32_t;
  using ::int_fast64_t;

  using ::int_least8_t;
  using ::int_least16_t;
  using ::int_least32_t;
  using ::int_least64_t;

  using ::intmax_t;

  using ::intptr_t;

  using ::uint8_t;
  using ::uint16_t;
  using ::uint32_t;
  using ::uint64_t;

  using ::uint_fast8_t;
  using ::uint_fast16_t;
  using ::uint_fast32_t;
  using ::uint_fast64_t;

  using ::uint_least8_t;
  using ::uint_least16_t;
  using ::uint_least32_t;
  using ::uint_least64_t;

  using ::uintmax_t;

  using ::uintptr_t;

  using ::ptrdiff_t;

  using ::size_t;

  using ::max_align_t;

  using nullptr_t = decltype(nullptr);

  using byte_t = unsigned char;

  enum class byte : byte_t { };

  }

#endif
