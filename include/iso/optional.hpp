#ifndef JESSY_ISO_OPTIONAL_HPP
#define JESSY_ISO_OPTIONAL_HPP

#include "core/error.hpp"
#include "iso/utility.hpp"

namespace os::iso
{

  struct nullopt_t
  {
    constexpr nullopt_t(int)
    {
    }
  };

  constexpr nullopt_t nullopt{42};

  template<typename ValueType>
  struct optional
  {

    // [optional.optional], constructors

    constexpr optional() noexcept
        : m_nothing{}
        , m_hasValue{}
    {
    }

    constexpr optional(nullopt_t) noexcept
        : optional{}
    {
    }

    optional(optional const & other)
        : m_hasValue{other.m_hasValue}
    {
      if (m_hasValue)
      {
        m_value = other.m_data.value;
      }
    }

    optional(optional && other)
        : m_hasValue{other.m_hasValue}
    {
      if (m_hasValue)
      {
        m_value = iso::move(other.m_data.value);
      }
    }

    template<typename... Args>
    constexpr optional(iso::in_place_t, Args &&... args)
        : m_value{iso::forward<Args>(args)...}
        , m_hasValue{true}
    {
    }

    optional(ValueType const & value)
        : m_value{value}
        , m_hasValue{true}
    {
    }

    optional(ValueType && value)
        : m_value{iso::move(value)}
        , m_hasValue{true}
    {
    }

    // [optional.optional], observers

    constexpr const ValueType * operator->() const
    {
      throw_on_empty();
      return &m_value;
    }

    constexpr ValueType * operator->()
    {
      throw_on_empty();
      return &m_value;
    }

    constexpr ValueType & operator*() &
    {
      throw_on_empty();
      return m_value;
    }

    constexpr ValueType const & operator*() const &
    {
      throw_on_empty();
      return m_value;
    }

    constexpr ValueType && operator*() &&
    {
      throw_on_empty();
      return iso::move(m_value);
    }

    constexpr ValueType const && operator*() const &&
    {
      throw_on_empty();
      return iso::move(m_value);
    }

    constexpr explicit operator bool() const noexcept
    {
      return m_hasValue;
    }

    constexpr bool has_value() const noexcept
    {
      return static_cast<bool>(*this);
    }

    constexpr ValueType & value() &
    {
      return **this;
    }

    constexpr ValueType const & value() const &
    {
      return **this;
    }

    constexpr ValueType && value() &&
    {
      return **this;
    }

    constexpr ValueType const && value() const &&
    {
      return **this;
    }

    template<typename OrType>
    constexpr ValueType value_or(OrType && alternative) const &
    {
      if (*this)
      {
        return **this;
      }
      return static_cast<ValueType>(iso::forward<OrType>(alternative));
    }

    template<typename OrType>
    constexpr ValueType value_or(OrType && alternative) &&
    {
      if (*this)
      {
        return iso::move(**this);
      }
      return static_cast<ValueType>(iso::forward<OrType>(alternative));
    }

    // [optional.optional], modifiers

    void reset() noexcept
    {
      if (*this)
      {
        m_value.~ValueType();
        m_hasValue = false;
      }
    }

    template<typename... Args>
    ValueType & emplace(Args &&... args)
    {
      if (*this)
      {
        m_value.~ValueType();
        new (&m_value) ValueType(iso::forward<Args>(args)...);
      }
      return m_value;
    }

  private:
    constexpr void throw_on_empty()
    {
      if (!*this)
      {
        core::panic("Illegal access to empty iso::optional");
      }
    }

    union
    {
      char m_nothing;
      ValueType m_value;
    };
    bool m_hasValue;
  };

}  // namespace os::iso

#endif
