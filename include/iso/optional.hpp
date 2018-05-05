#ifndef JESSY_ISO_OPTIONAL_HPP
#define JESSY_ISO_OPTIONAL_HPP

#include "iso/utility.hpp"
#include "core/error.hpp"

namespace os::iso
  {

  struct nullopt_t
    {
    constexpr nullopt_t(int) { }
    };

  constexpr nullopt_t nullopt{42};

  template<typename ValueType>
  struct optional
    {
    constexpr optional() : m_data{}, m_hasValue{} { }
    constexpr optional(nullopt_t) : optional{} { }

    optional(optional const & other)
      : m_hasValue{other.m_hasValue}
      {
      if(m_hasValue)
        {
        m_data.value = other.m_data.value;
        }
      }

    optional(optional && other)
      : m_hasValue{other.m_hasValue}
      {
      if(m_hasValue)
        {
        m_data.value = core::move(other.m_data.value);
        }
      }

    optional(ValueType const & value)
      : m_hasValue{true}
      {
      m_data.value = value;
      }

    optional(ValueType && value)
      : m_hasValue{true}
      {
      m_data.value = core::move(value);
      }

    constexpr ValueType & value() &
      {
      if(!m_hasValue)
        {
        core::panic("Illegal access to empty core::optional");
        }

      return m_data.value;
      }

    constexpr ValueType const & value() const &
      {
      if(!m_hasValue)
        {
        core::panic("Illegal access to empty core::optional");
        }

      return m_data.value;
      }

    constexpr ValueType && value() &&
      {
      if(!m_hasValue)
        {
        core::panic("Illegal access to empty core::optional");
        }

      return core::move(m_data.value);
      }

    constexpr ValueType const && value() const &&
      {
      if(!m_hasValue)
        {
        core::panic("Illegal access to empty core::optional");
        }

      return core::move(m_data.value);
      }

    constexpr operator bool() const
      {
      return m_hasValue;
      }

    template<typename Callable>
    constexpr  map(Callable function)
      {
      if(m_hasValue)
        {
        return optional{function(m_data.value)};
        }

      return optional{};
      }

    private:
      union storage { char base; ValueType value; } m_data;
      bool m_hasValue;
    };

  }

#endif
