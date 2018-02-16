#ifndef JESSY_CORE_ERROR_HPP
#define JESSY_CORE_ERROR_HPP

namespace os::core
  {

  struct panic_location
    {
    char const * const function;
    char const * const file;
    };

  [[noreturn]] void panic(panic_location const location, char const * const message);

  }

#endif
