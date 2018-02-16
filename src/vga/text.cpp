#include "vga/text.hpp"
#include "core/memory.hpp"

namespace os::vga::text
  {

  using vga_text_buffer_cell = os::core::uint16_t;

  /**
   * @brief The global text buffer state
   */
  namespace
    {
    /**
     * The current offset into to VGA text buffer (e.g the next "free" cell)
     */
    os::core::ptrdiff_t gCurrentCell{};
    }

  /**
   * @brief Global Constants
   */
  namespace
    {
    /**
     * The base address of the VGA text buffer
     *
     * @note Each "cell" of the VGA text buffer consists of a color code + the actual ASCII character code.
     */
    auto const cVGATextBufferBase = reinterpret_cast<vga_text_buffer_cell volatile *>(0xb8000ull);

    /**
     * An "empty" VGA text word (a white space on black background)
     */
    uint16_t constexpr cVGAClearWord = 0x0f20;

    /**
     * The number of columns in the VGA text buffer
     */
    auto constexpr cVGATextBufferColumns = 80;

    /**
     * The number of rows in the VGA text buffer
     */
    auto constexpr cVGATextBufferRows = 25;
    }

  /**
   * Internal Helper Functions
   */
  namespace
    {
    /**
     * Get a reference to the current VGA text buffer cell
     */
    decltype(auto) cell()
      {
      return *(cVGATextBufferBase + gCurrentCell);
      }

    /**
     * Get a reference to a speficic cell in the VGA text buffer
     */
    decltype(auto) cell(os::core::uint16_t column, os::core::uint16_t row)
      {
      return *(cVGATextBufferBase + column + row * cVGATextBufferColumns);
      }

    /**
     * Scroll up the complete VGA text buffer
     */
    auto scroll_up()
      {
      for(auto row = 1; row < cVGATextBufferRows; ++row)
        {
        for(auto column = 0; column < cVGATextBufferColumns; ++column)
          {
          cell(column, row - 1) = cell(column, row);
          }
        }
      gCurrentCell -= gCurrentCell % cVGATextBufferColumns;
      os::core::set_memory(&cell(), cVGAClearWord, cVGATextBufferColumns);
      }

    /**
     * Move the insertion point to the next cell, scrolling the screen if required
     */
    auto move_to_next_cell()
      {
      auto const currentCell = gCurrentCell;
      if(currentCell + 1 >= cVGATextBufferColumns * cVGATextBufferRows)
        {
        scroll_up();
        }
      else
        {
        ++gCurrentCell;
        }
      }

    /**
     * Move the insertion point to the start of the next line
     */
    auto move_to_next_line()
      {
      auto const currentRow = gCurrentCell / cVGATextBufferColumns;
      if(currentRow >= cVGATextBufferRows - 1)
        {
        scroll_up();
        }
      else
        {
        gCurrentCell = (currentRow + 1) * cVGATextBufferColumns;
        }
      }
    }

  void print(color color, char const * const text)
    {
    for(auto idx = 0ull; text[idx]; ++idx)
      {
      cell() = static_cast<os::core::uint16_t>(color) + text[idx];
      move_to_next_cell();
      }
    }

  void print_line(color color, char const * const text)
    {
    print(color, text);
    move_to_next_line();
    }

  void clear_screen()
    {
    os::core::set_memory(&cell(0, 0), cVGAClearWord, cVGATextBufferColumns * cVGATextBufferRows);
    gCurrentCell = 0;
    }

  }
