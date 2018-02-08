#include "vga/text.hpp"

namespace os::vga::text
  {

  /**
   * @brief The global text buffer state
   */
  namespace
    {
    os::core::ptrdiff_t gBufferOffset{};
    }

  uint16_t volatile & buffer()
    {
    return (*reinterpret_cast<uint16_t volatile *>(0xb8000 + gBufferOffset));
    }

  void print(color color, char const * const text)
    {
    for(auto idx = 0ull; text[idx]; ++idx)
      {
      buffer() = static_cast<os::core::uint16_t>(color) + text[idx];
      gBufferOffset+=2;
      }
    }

  void clear_screen()
    {
    }

  }
