# vim: ft=cmake ts=2 sw=2 et

string(APPEND
  CMAKE_CXX_FLAGS
  " -Wextra -Werror -pedantic-errors"
  )
set(CMAKE_CXX_STANDARD
  "17"
  )
set(CMAKE_CXX_EXTENSIONS
  OFF
  )
set(CMAKE_CXX_STANDARD_REQUIRED
  ON
  )
