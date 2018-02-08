#include "vga/text.hpp"

namespace os::vga::text
  {

  /**
   * @brief The global text buffer state
   */
  namespace
    {

    }

  uint16_t volatile & buffer(os::core::ptrdiff_t offset)
    {
    return (*reinterpret_cast<uint16_t volatile *>(0xb8000 + offset * 2));
    }

  void print(color color, char const * const text)
    {
    for(auto idx = 0ull; text[idx]; ++idx)
      {
      buffer(idx) = static_cast<os::core::uint16_t>(color) + text[idx];
      }
    }

  void clear()
    {

    }

  }
