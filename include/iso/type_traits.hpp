#ifndef JESSY_ISO_TYPE_TRAITS_HPP
#define JESSY_ISO_TYPE_TRAITS_HPP

#include "iso/cstddef.hpp"

namespace os::iso
  {

  namespace impl::type_traits
    {
    /**
     * A simple helper type to allow differentiation of return type sizes
     */
    struct size_two
      {
      char filler[2]{};
      };
    }

  /**
   * A helper type alias to map arbitrary types to void
   *
   * This type alias is especially useful to detect malformed typed when employing SFINAE.
   *
   * @tparam ... An arbitrary number of types to map to void
   */
  template<typename ...>
  using void_t = void;

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

  /**
   * Calculate the type resulting from removing the top-level const-qualification from the given type
   *
   * @tparam Type The type to remove const-qualification from
   */
  template<typename Type> struct remove_const { using type = Type; };
  template<typename Type> struct remove_const<Type const> { using type = Type; };

  /**
   * Calculate the type resulting from removing the top-level const-qualification from the given type
   *
   * @tparam Type The type to remove const-qualification from
   * @note This is a convenience alias for os::iso::remove_const<Type>::type
   */
  template<typename Type> using remove_const_t = typename remove_const<Type>::type;

  /**
   * Static test suite for os::iso::remove_const
   */
  namespace impl::type_traits::test::remove_const
    {
    static_assert(is_same_v<int, remove_const_t<int>>);
    static_assert(is_same_v<int, remove_const_t<int const>>);
    static_assert(is_same_v<int volatile, remove_const_t<int volatile>>);
    static_assert(is_same_v<int volatile, remove_const_t<int const volatile>>);

    static_assert(is_same_v<iso::remove_const<int>::type, remove_const_t<int>>);
    static_assert(is_same_v<iso::remove_const<int const>::type, remove_const_t<int const>>);
    static_assert(is_same_v<iso::remove_const<int volatile>::type, remove_const_t<int volatile>>);
    static_assert(is_same_v<iso::remove_const<int const volatile>::type, remove_const_t<int const volatile>>);
    }

  /**
   * Calculate the type resulting from removing the top-level volatile-qualification from the given type
   *
   * @tparam Type The type to remove volatile-qualification from
   */
  template<typename Type> struct remove_volatile { using type = Type; };
  template<typename Type> struct remove_volatile<Type volatile> { using type = Type; };

  /**
   * Calculate the type resulting from removing the top-level volatile-qualification from the given type
   *
   * @tparam Type The type to remove volatile-qualification from
   * @note This is a convenience alias for os::iso::remove_volatile<Type>::type
   */
  template<typename Type> using remove_volatile_t = typename remove_volatile<Type>::type;

  /**
   * Static test suite for os::iso::remove_volatile
   */
  namespace impl::type_traits::test::remove_volatile
    {
    static_assert(is_same_v<int, remove_volatile_t<int>>);
    static_assert(is_same_v<int, remove_volatile_t<int volatile>>);
    static_assert(is_same_v<int const, remove_volatile_t<int const>>);
    static_assert(is_same_v<int const, remove_volatile_t<int const volatile>>);

    static_assert(is_same_v<iso::remove_volatile<int>::type, remove_volatile_t<int>>);
    static_assert(is_same_v<iso::remove_volatile<int volatile>::type, remove_volatile_t<int volatile>>);
    static_assert(is_same_v<iso::remove_volatile<int const>::type, remove_volatile_t<int const>>);
    static_assert(is_same_v<iso::remove_volatile<int const volatile>::type, remove_volatile_t<int const volatile>>);
    }

  /**
   * Calculate the type resulting from removing the top-level cv-qualification from the given type
   *
   * @tparam Type The type to remove cv-qualification from
   */
  template<typename Type> struct remove_cv { using type = remove_volatile_t<remove_const_t<Type>>; };

  /**
   * Calculate the type resulting from removing the top-level cv-qualification from the given type
   *
   * @tparam Type The type to remove cv-qualification from
   * @note This is a convenience alias for os::iso::remove_cv<Type>::type
   */
  template<typename Type> using remove_cv_t = typename remove_cv<Type>::type;

  /**
   * Static test suite for os::iso::remove_cv
   */
  namespace impl::type_traits::test::remove_cv
    {
    static_assert(is_same_v<int, remove_cv_t<int>>);
    static_assert(is_same_v<int, remove_cv_t<int const>>);
    static_assert(is_same_v<int, remove_cv_t<int volatile>>);
    static_assert(is_same_v<int, remove_cv_t<int const volatile>>);

    static_assert(is_same_v<iso::remove_cv<int>::type, remove_cv_t<int>>);
    static_assert(is_same_v<iso::remove_cv<int volatile>::type, remove_cv_t<int volatile>>);
    static_assert(is_same_v<iso::remove_cv<int const>::type, remove_cv_t<int const>>);
    static_assert(is_same_v<iso::remove_cv<int const volatile>::type, remove_cv_t<int const volatile>>);
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
   * A meta-function to declare a reference to and object of type @p Type
   *
   * This function allows the "instantiation" of an object without using constructors. It therefore can only be used in
   * unevaluated contexts.
   *
   * @tparam Type The type of the object to "instantiate"
   */
  template<typename Type>
  add_rvalue_reference_t<Type> declval();

  /**
   * Take the address of any object, ignoring overloaded <code>operator &</code>
   */
  template<typename Type>
  constexpr Type * addressof(Type & object) { return ADDRESSOF(object); }

  template<typename Type>
  Type * addressof(Type const &&) = delete;

  /**
   * Calculate the underlying type of an enumeration type
   *
   * This trait provides a member type alias @p type that is equal to the underlying type of @p Type. The behaviour is
   * undefined if @p Type is not an enumeration type.
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

  /**
   * Select one type or the other, depending on the value of @p If
   *
   * This trait provides a member type alias @p type that is equal to @p Then if @p If is @p true, and @p Else otherwise
   *
   * @tparam If The codition under which the first type shall be selected
   * @tparam Then The type to be selected if @p If evaluates to true
   * @tparam Else The type to be selected if @p If evaluates to false
   */
  template<bool If, typename Then, typename Else>
  struct conditional
    {
    using type = Then;
    };

  /**
   * Specialisation of os::iso::conditional for the case that @p If evaluates to false
   */
  template<typename Then, typename Else>
  struct conditional<false, Then, Else>
    {
    using type = Else;
    };

  /**
   * Select one type or the other, depending on the value of @p If
   *
   * @tparam If The codition under which the first type shall be selected
   * @tparam Then The type to be selected if @p If evaluates to true
   * @tparam Else The type to be selected if @p If evaluates to false
   *
   * @note This is a convenience alias form os::iso::conditional<If, Then, Else>::type
   */
  template<bool If, typename Then, typename Else>
  using conditional_t = typename conditional<If, Then, Else>::type;

  /**
   * Static test suite for os::iso::conditional
   */
  namespace impl::type_traits::test::conditional
    {
    static_assert(is_same_v<void, conditional_t<true, void, int>>);
    static_assert(is_same_v<int, conditional_t<false, void, int>>);

    static_assert(is_same_v<typename iso::conditional<true, void, int>::type, conditional_t<true, void, int>>);
    static_assert(is_same_v<typename iso::conditional<false, void, int>::type, conditional_t<false, void, int>>);
    }

  /**
   * Test if a given type is a union
   *
   * This trait provides a static member of type @p bool that is either @p true or @p false, depending on whether
   * @p Type is a @p union or not. Objects of this trait are implicitely convertible to @p bool.
   *
   * @tparam Type The type to test
   */
  template<typename Type>
  struct is_union : integral_constant<bool, IS_UNION(Type)> { };

  /**
   * Test if a given type is a union
   *
   * @tparam Type The type to test
   * @note This is a convenience alias for os::iso::is_union<Type>::value
   */
  template<typename Type>
  bool constexpr is_union_v = is_union<Type>::value;

  /**
   * Static test suite for os::iso::is_union
   */
  namespace impl::type_traits::test::is_union
    {
    static_assert(!is_union_v<void>);
    static_assert(is_union_v<union U>);

    static_assert(is_union_v<void> == iso::is_union<void>{});
    static_assert(is_union_v<union U> == iso::is_union<union V>{});
    }

  namespace impl::type_traits
    {
    template<typename Type>
    char is_class_test(int Type::*);

    template<typename Type>
    size_two is_class_test(...);
    }

  /**
   * Test if a given type is a class type
   *
   * This trait provides a static member of type @p bool that is either @p true or @p false, depending on whether
   * @p Type is a @p class-type or not. Objects of this trait are implicitely convertible to @p bool.
   *
   * @tparam Type The type to test
   */
  template<typename Type>
  struct is_class : integral_constant<
    bool,
    sizeof(impl::type_traits::is_class_test<Type>(0)) == 1 &&
    !is_union_v<Type>
    > { };

  /**
   * Test if a given type is a class type
   *
   * @tparam Type The type to test
   * @note This is a convenience alias for os::iso::is_class<Type>
   */
  template<typename Type>
  bool constexpr is_class_v = is_class<Type>{};

  namespace impl::type_traits
    {
    template<typename Base>
    true_type is_base_of_test(Base *);

    template<typename Base>
    false_type is_base_of_test(void *);

    template<typename Base, typename Derived>
    using is_base_of_test_type = decltype(is_base_of_test<Base>(declval<Derived *>()));

    template<typename Base, typename Derived, typename = void>
    struct is_base_of_test_type2 : true_type { };

    template<typename Base, typename Derived>
    struct is_base_of_test_type2<Base, Derived, void_t<is_base_of_test_type<Base, Derived>>> :
        is_base_of_test_type<Base, Derived> {};
    }

  /**
   * Test if @p Base is a base class of @p Derived
   *
   * This trait provides a static member of type @p bool that is either @p true or @p false, depending on whether
   * @p Base is a base class of @p Derived or not. Objects of this trait are implicitely convertible to @p bool.
   *
   * @tparam Base The suspected base class
   * @tparam Derived The type to test
   */
  template<typename Base, typename Derived>
  struct is_base_of : conditional_t<
    is_class_v<Base> && is_class_v<Derived>,
    impl::type_traits::is_base_of_test_type2<Base, Derived>,
    false_type
    > { };

  /**
   * Test if @p Base is a base class of @p Derived
   *
   * @tparam Base The suspected base class
   * @tparam Derived The type to test
   * @note This is a convenience alias for os::iso::is_base_of<Base, Derived>
   */
  template<typename Base, typename Derived>
  bool constexpr is_base_of_v = is_base_of<Base, Derived>{};

  /**
   * Static test suite for os::iso::is_base_of
   */
  namespace impl::type_traits::test::is_base_of
    {
    struct base { };
    struct derived : base { };

    static_assert(is_base_of_v<base, derived>);
    static_assert(!is_base_of_v<derived, base>);
    static_assert(!is_base_of_v<void, derived>);
    static_assert(!is_base_of_v<base, void>);
    static_assert(is_base_of_v<base, base>);

    static_assert(is_base_of_v<base, derived> == iso::is_base_of<base, derived>{});
    static_assert(is_base_of_v<derived, base> == iso::is_base_of<derived, base>{});
    }

  /**
   * Test if @p Type names an array type
   *
   * This trait provides a static member of type @p bool that is either @p true or @p false, depending on whether @p Type names
   * an arrya type or not. Objects of this trait are implicitely convertible to @p bool.
   *
   * @tparam Type The type to test
   */
  template<typename Type>
  struct is_array : false_type { };

  template<typename Type>
  struct is_array<Type[]> : true_type { };

  template<typename Type, iso::size_t Dimension>
  struct is_array<Type[Dimension]> : true_type { };

  /**
   * Test if @p Type names an array type
   *
   * @tparam Type The type to test
   * @note This is a convenience alias for os::iso::is_array<Type>
   */
  template<typename Type>
  bool constexpr is_array_v = is_array<Type>{};

  /**
   * Static test suite for os::iso::is_array
   */
  namespace impl::type_traits::test::is_array
    {
    static_assert(!is_array_v<int>);
    static_assert(is_array_v<int[]>);
    static_assert(is_array_v<int[42]>);

    static_assert(is_array_v<int> == iso::is_array<int>{});
    static_assert(is_array_v<int[]> == iso::is_array<int[]>{});
    static_assert(is_array_v<int[42]> == iso::is_array<int[42]>{});
    }

  /**
   * Test if @p Type names an lvalue reference type
   *
   * This trait provides a static member of type @p bool that is either @p true or @p false, depending on whether @p Type names
   * an lvalue reference type or not. Objects of this trait are implicitely convertible to @p bool.
   *
   * @tparam Type The type to test
   */
  template<typename Type> struct is_lvalue_reference : false_type { };
  template<typename Type> struct is_lvalue_reference<Type &> : true_type { };

  /**
   * Test if @p Type names an lvalue reference type
   *
   * @tparam Type The type to test
   * @note This is a convenience alias for iso::is_lvalue_reference<Type>
   */
  template<typename Type> bool constexpr is_lvalue_reference_v = is_lvalue_reference<Type>{};

  /**
   * Static test suite for os::iso::is_lvalue_reference
   */
  namespace impl::type_traits::test::is_lvalue_reference
    {
    static_assert(!is_lvalue_reference_v<int>);
    static_assert(!is_lvalue_reference_v<int &&>);
    static_assert(is_lvalue_reference_v<int &>);
    static_assert(is_lvalue_reference_v<int const &>);
    static_assert(is_lvalue_reference_v<int volatile &>);
    static_assert(is_lvalue_reference_v<int const volatile &>);

    static_assert(is_lvalue_reference_v<int> == iso::is_lvalue_reference<int>{});
    static_assert(is_lvalue_reference_v<int &&> == iso::is_lvalue_reference<int &&>{});
    static_assert(is_lvalue_reference_v<int &> == iso::is_lvalue_reference<int &>{});
    static_assert(is_lvalue_reference_v<int const &> == iso::is_lvalue_reference<int const &>{});
    static_assert(is_lvalue_reference_v<int volatile &> == iso::is_lvalue_reference<int volatile &>{});
    static_assert(is_lvalue_reference_v<int const volatile &> == iso::is_lvalue_reference<int const volatile &>{});
    }

  /**
   * Test if @p Type names an rvalue reference type
   *
   * This trait provides a static member of type @p bool that is either @p true or @p false, depending on whether @p Type names
   * an rvalue reference type or not. Objects of this trait are implicitely convertible to @p bool.
   *
   * @tparam Type The type to test
   */
  template<typename Type> struct is_rvalue_reference : false_type { };
  template<typename Type> struct is_rvalue_reference<Type &&> : true_type { };

  /**
   * Test if @p Type names an rvalue reference type
   *
   * @tparam Type The type to test
   * @note This is a convenience alias for iso::is_rvalue_reference<Type>
   */
  template<typename Type> bool constexpr is_rvalue_reference_v = is_rvalue_reference<Type>{};

  /**
   * Static test suite for os::iso::is_rvalue_reference
   */
  namespace impl::type_traits::test::is_rvalue_reference
    {
    static_assert(!is_rvalue_reference_v<int>);
    static_assert(!is_rvalue_reference_v<int &>);
    static_assert(is_rvalue_reference_v<int &&>);
    static_assert(is_rvalue_reference_v<int const &&>);
    static_assert(is_rvalue_reference_v<int volatile &&>);
    static_assert(is_rvalue_reference_v<int const volatile &&>);

    static_assert(is_rvalue_reference_v<int> == iso::is_rvalue_reference<int>{});
    static_assert(is_rvalue_reference_v<int &> == iso::is_rvalue_reference<int &>{});
    static_assert(is_rvalue_reference_v<int &&> == iso::is_rvalue_reference<int &&>{});
    static_assert(is_rvalue_reference_v<int const &&> == iso::is_rvalue_reference<int const &&>{});
    static_assert(is_rvalue_reference_v<int volatile &&> == iso::is_rvalue_reference<int volatile &&>{});
    static_assert(is_rvalue_reference_v<int const volatile &&> == iso::is_rvalue_reference<int const volatile &&>{});
    }

  /**
   * Test if @p Type names an reference type
   *
   * This trait provides a static member of type @p bool that is either @p true or @p false, depending on whether @p Type names
   * an reference type or not. Objects of this trait are implicitely convertible to @p bool.
   *
   * @tparam Type The type to test
   */
  template<typename Type>
  struct is_reference : integral_constant<bool, is_lvalue_reference_v<Type> || is_rvalue_reference_v<Type>> { };

  /**
   * Test if @p Type names an rvalue reference type
   *
   * @tparam Type The type to test
   * @note This is a convenience alias for iso::is_reference<Type>
   */
  template<typename Type> bool constexpr is_reference_v = is_reference<Type>{};

  /**
   * Static test suite for os::iso::is_reference
   */
  namespace impl::type_traits::test::is_reference
    {
    static_assert(!is_reference_v<int>);
    static_assert(is_reference_v<int &>);
    static_assert(is_reference_v<int &&>);
    static_assert(is_reference_v<int const &&>);
    static_assert(is_reference_v<int volatile &&>);
    static_assert(is_reference_v<int const volatile &&>);

    static_assert(is_reference_v<int> == iso::is_reference<int>{});
    static_assert(is_reference_v<int &> == iso::is_reference<int &>{});
    static_assert(is_reference_v<int &&> == iso::is_reference<int &&>{});
    static_assert(is_reference_v<int const &&> == iso::is_reference<int const &&>{});
    static_assert(is_reference_v<int volatile &&> == iso::is_reference<int volatile &&>{});
    static_assert(is_reference_v<int const volatile &&> == iso::is_reference<int const volatile &&>{});
    }

  }

#endif
