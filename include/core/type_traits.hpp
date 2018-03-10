#ifndef JESSY_CORE_TYPE_TRAITS_HPP
#define JESSY_CORE_TYPE_TRAITS_HPP

namespace os::core
  {

  template<typename Type> struct remove_reference { using type = Type; };
  template<typename Type> struct remove_reference<Type &> { using type = Type; };
  template<typename Type> struct remove_reference<Type &&> { using type = Type; };
  template<typename Type> using remove_reference_t = typename remove_reference<Type>::type;

  }

#endif
