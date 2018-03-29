#ifndef JESSY_ISO_SOURCE_LOCATION_HPP
#define JESSY_ISO_SOURCE_LOCATION_HPP

#include "iso/cstdint.hpp"

namespace os::iso
  {

  struct source_location
    {
    static constexpr source_location current(char const * file = __builtin_FILE(),
                                             char const * function = __builtin_FUNCTION(),
                                             int line = __builtin_LINE(),
                                             int column = 0) noexcept
      {
      auto location = source_location{};
      location.m_file = file;
      location.m_function = function;
      location.m_line = line;
      location.m_file = file;
      return location;
      }

    constexpr auto line() const noexcept { return m_line; }
    constexpr auto column() const noexcept { return m_column; }
    constexpr auto file_name() const noexcept { return m_file; }
    constexpr auto function_name() const noexcept { return m_function; }

    private:
      char const * m_file;
      char const * m_function;
      uint_least32_t m_line;
      uint_least32_t m_column;
    };

  }

#endif
