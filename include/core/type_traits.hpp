#ifndef JESSY_CORE_TYPE_TRAITS_HPP
#define JESSY_CORE_TYPE_TRAITS_HPP

namespace os::core
  {

  /**
   * Calculate the type resulting from removing the ref-qualifier from the given type
   */
  template<typename Type> struct remove_reference { using type = Type; };
  template<typename Type> struct remove_reference<Type &> { using type = Type; };
  template<typename Type> struct remove_reference<Type &&> { using type = Type; };

  /**
   * Calculate the type resulting from removing the ref-qualifier from the given type
   *
   * @note This is a convenience alias for os::core::remove_reference<Type>::type
   */
  template<typename Type> using remove_reference_t = typename remove_reference<Type>::type;

  }

#endif
