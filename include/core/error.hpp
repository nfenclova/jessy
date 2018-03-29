#ifndef JESSY_CORE_ERROR_HPP
#define JESSY_CORE_ERROR_HPP

#include "iso/source_location.hpp"

namespace os::core
  {

  [[noreturn]] void panic(iso::source_location const location, char const * const message);

  }

#endif
