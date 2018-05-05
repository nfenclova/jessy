#ifndef JESSY_CORE_ERROR_HPP
#define JESSY_CORE_ERROR_HPP

#include "iso/source_location.hpp"

namespace os::core
  {

  [[noreturn]] void panic(char const * const message, iso::source_location const location = iso::source_location::current());

  }

#endif
