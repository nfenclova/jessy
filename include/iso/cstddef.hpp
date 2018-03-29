#ifndef JESSY_ISO_CSTDDEF_HPP
#define JESSY_ISO_CSTDDEF_HPP

#include <stddef.h>

namespace os::iso
  {

  using ::ptrdiff_t;

  using ::size_t;

  using ::max_align_t;

  using nullptr_t = decltype(nullptr);

  using byte_t = unsigned char;

  enum class byte : byte_t { };

  }

#endif
