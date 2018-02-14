#include "vga/text.hpp"
#include "core/memory.hpp"

namespace os::vga::text
  {

  /**
   * @brief The global text buffer state
   */
  namespace
    {
    os::core::ptrdiff_t gBufferOffset{};
    }

  /**
   * @brief Global Constants
   */
  namespace
    {
    auto const cVGATextBufferBase = reinterpret_cast<uint16_t volatile *>(0xb8000ull);

    uint16_t constexpr cVGAClearWord = 0x0f20;

    auto constexpr cVGATextBufferRows = 80;
    auto constexpr cVGATextBufferColumns = 25;
    }

  uint16_t volatile & buffer()
    {
    return *(cVGATextBufferBase + gBufferOffset);
    }

  void print(color color, char const * const text)
    {
    for(auto idx = 0ull; text[idx]; ++idx)
      {
      buffer() = static_cast<os::core::uint16_t>(color) + text[idx];
      ++gBufferOffset;
      }
    }

  void clear_screen()
    {
    os::core::set_memory(cVGATextBufferBase,
                         cVGAClearWord,
                         cVGATextBufferRows * cVGATextBufferColumns / sizeof(cVGAClearWord));
    }

  }
