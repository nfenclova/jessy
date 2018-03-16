#ifndef JESSY_CORE_ERROR_HPP
#define JESSY_CORE_ERROR_HPP

#include "core/source_location.hpp"

namespace os::core
  {

  [[noreturn]] void panic(source_location const location, char const * const message);

  }

#endif
