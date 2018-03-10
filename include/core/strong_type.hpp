#ifndef JESSY_STRONG_TYPE_HPP
#define JESSY_STRONG_TYPE_HPP

#include "core/utility.hpp"

namespace os::core
  {

  template<typename UnderlyingType, typename TagType>
  struct strong_type
    {
    explicit constexpr strong_type(UnderlyingType const & value) : m_value{value} { };
    explicit constexpr strong_type(UnderlyingType && value) : m_value{core::move(value)} { };

    explicit constexpr operator UnderlyingType() const
      {
      return m_value;
      }

    private:
      UnderlyingType m_value;
    };

  }

#endif
