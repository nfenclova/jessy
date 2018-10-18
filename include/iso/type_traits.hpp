#ifndef JESSY_ISO_TYPE_TRAITS_HPP
#define JESSY_ISO_TYPE_TRAITS_HPP

namespace os::iso
  {

  namespace impl::type_traits
    {
    struct size_two
      {
      char filler[2]{};
      };
    }

  /**
   * Wrap a constant value of integral type into a type
   *
   * @note [meta.help]
   *
   * @tparam ValueType The type of value to wrap
   * @tparam Value The value to wrap
   */
  template<typename ValueType, ValueType Value>
  struct integral_constant
    {
    using value_type = ValueType;
    using type = integral_constant;

    static ValueType constexpr value = Value;

    constexpr operator value_type() const noexcept { return value; }
    constexpr value_type operator()() const noexcept { return value; }
    };

  /**
   * Convenience alias for a type representing false
   */
  using false_type = integral_constant<bool, false>;

  /**
   * Convenience alias for a type representing true
   */
  using true_type = integral_constant<bool, true>;

  /**
   * Check if two types are the same
   *
   * @note Base case for differing types
   *
   * @tparam LType The left-hand type
   * @tparam RType The right-hand type
   */
  template<typename LType, typename RType>
  struct is_same : false_type { };

  /**
   * Check if two types are the same
   *
   * @note Special case for for identical types
   */
  template<typename Type>
  struct is_same<Type, Type> : true_type { };

  /**
   * Convenience alias for accessing the @p type member of #os::iso::is_same
   *
   * @tparam LType The left-hand type
   * @tparam RType The right-hand type
   */
  template<typename LType, typename RType>
  using is_same_t = typename is_same<LType, RType>::type;

  /**
   * Convenience alias for accessing the @p value member of #os::iso::is_same
   *
   * @tparam LType The left-hand type
   * @tparam RType The right-hand type
   */
  template<typename LType, typename RType>
  constexpr bool is_same_v = is_same_t<LType, RType>{};

  /**
   * Static test suite for os::iso::is_same
   */
  namespace impl::type_traits::test::is_same
    {
    static_assert(!os::iso::is_same<int, char>::value);
    static_assert(!os::iso::is_same<int, char>{});
    static_assert(!os::iso::is_same<int, char>{}());
    static_assert(!os::iso::is_same_v<int, char>);

    static_assert(os::iso::is_same<int, int>::value);
    static_assert(os::iso::is_same<int, int>{});
    static_assert(os::iso::is_same<int, int>{}());
    static_assert(os::iso::is_same_v<int, int>);
    }

  /**
   * Calculate the type resulting from removing the ref-qualifier from the given type
   */
  template<typename Type> struct remove_reference { using type = Type; };
  template<typename Type> struct remove_reference<Type &> { using type = Type; };
  template<typename Type> struct remove_reference<Type &&> { using type = Type; };

  /**
   * Calculate the type resulting from removing the ref-qualifier from the given type
   *
   * @note This is a convenience alias for os::iso::remove_reference<Type>::type
   */
  template<typename Type> using remove_reference_t = typename remove_reference<Type>::type;

  /**
   * Static test suite for os::iso::remove_reference
   */
  namespace impl::type_traits::test::remove_reference
    {
    static_assert(!os::iso::is_same_v<int &, os::iso::remove_reference<int &>::type>);
    static_assert(!os::iso::is_same_v<int &, os::iso::remove_reference_t<int &>>);

    static_assert(os::iso::is_same_v<int, os::iso::remove_reference<int &>::type>);
    static_assert(os::iso::is_same_v<int, os::iso::remove_reference_t<int &>>);
    }

  namespace impl::type_traits
    {
    struct is_referenceable_test
      {
      template<typename Type>
      static Type & test(int);

      template<typename Type>
      static size_two test(...);
      };
    }

  /**
   * Check if the given type can be used to bind references
   */
  template<typename Type>
  struct is_referenceable :
    integral_constant<
      bool,
      !is_same_v<
        decltype(impl::type_traits::is_referenceable_test::test<Type>(0)),
        impl::type_traits::size_two>
      >
    { };

  /**
   * Check if the given type can be used to bind references
   *
   * @note This is a convenience alias for os::iso::is_referenceable<Type>::value
   */
  template<typename Type>
  constexpr bool is_referenceable_v = is_referenceable<Type>{};

  namespace impl::type_traits
    {
    template<typename Type, bool = is_referenceable_v<Type>>
    struct add_rvalue_reference_select
      {
      using type = Type;
      };

    template<typename Type>
    struct add_rvalue_reference_select<Type, true>
      {
      using type = Type &&;
      };
    }

  /**
   * @brief Calculate the type arising from adding @p && to the given type
   *
   * This trait provides a member type @p type that is equal to <code>Type &&</code> iff.
   * @p os::iso::is_referenceable_v is equal to @p true. Otherwise, @p type will be equal to @p Type
   */
  template<typename Type>
  struct add_rvalue_reference : impl::type_traits::add_rvalue_reference_select<Type> { };

  /**
   * Calculate the type arising from adding @p && to the given type
   *
   * @note This is a convenience alias for os::iso::add_rvalue_reference<Type>::type
   */
  template<typename Type>
  using add_rvalue_reference_t = typename add_rvalue_reference<Type>::type;

  /**
   * Static test suite for os::iso::add_rvalue_reference
   */
  namespace impl::type_traits::test::add_rvalue_reference
    {
    static_assert(is_same_v<int &&, add_rvalue_reference_t<int>>);
    static_assert(is_same_v<int &&, add_rvalue_reference_t<int &&>>);
    static_assert(is_same_v<int &,  add_rvalue_reference_t<int &>>);
    }

  namespace impl::type_traits
    {
    template<typename Type, bool = is_referenceable_v<Type>>
    struct add_lvalue_reference_select
      {
      using type = Type;
      };

    template<typename Type>
    struct add_lvalue_reference_select<Type, true>
      {
      using type = Type &;
      };
    }

  /**
   * @brief Calculate the type arising from adding @p & to the given type
   *
   * This trait provides a member type @p type that is equal to <code>Type &</code> iff.
   * @p os::iso::is_referenceable_v is equal to @p true. Otherwise, @p type will be equal to @p Type
   */
  template<typename Type>
  struct add_lvalue_reference : impl::type_traits::add_lvalue_reference_select<Type> { };

  /**
   * Calculate the type arising from adding @p & to the given type
   *
   * @note This is a convenience alias for os::iso::add_lvalue_reference<Type>::type
   */
  template<typename Type>
  using add_lvalue_reference_t = typename add_lvalue_reference<Type>::type;

  /**
   * Static test suite for os::iso::add_lvalue_reference
   */
  namespace impl::type_traits::test::add_lvalue_reference
    {
    static_assert(is_same_v<int &, add_lvalue_reference_t<int>>);
    static_assert(is_same_v<int &, add_lvalue_reference_t<int &&>>);
    static_assert(is_same_v<int &, add_lvalue_reference_t<int &>>);
    }

  /**
   * Calculate the underlying type of an enumeration type
   */
  template<typename Type>
  struct underlying_type
    {
    using type = UNDERLYING_TYPE(Type);
    };

  /**
   * Calculate the underlying type of an enumeration type
   *
   * @note This is a convenience alias for os::iso::underlying_type<Type>::type
   */
  template<typename Type>
  using underlying_type_t = typename underlying_type<Type>::type;

  }

#endif
