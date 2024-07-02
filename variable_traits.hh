#ifndef VARIABLE_TRAITS_HH
#define VARIABLE_TRAITS_HH

#include <tuple>
#include <type_traits>

namespace internal{

/**
 * 非成员变量类型萃取
 * @type: 变量类型
 */
template <typename T>
struct variable_type
{
    using type = T;
};

/**
 * 成员变量类型萃取
 * @type: 成员变量类型
 */
template <typename Class, typename T>
struct variable_type <T Class::*>
{
    using type = T;
};
}

/**
 * 变量类型萃取包装函数
 */
template <typename T>
using variable_type_t = typename internal::variable_type<T>::type;

namespace internal{

/**
 * 记录变量类型萃取的基本信息
 * @type: 变量类型
 * @is_member: 是否成员变量
 * @is_const: 是否常量变量
 */
template <typename T>
struct basic_variable_traits
{
  using type = variable_type_t<T>;
  static constexpr bool is_member = std::is_member_pointer<T>::value;
  static constexpr bool is_const = std::is_const<T>::value;
};
}

/**
 * 变量类型萃取，继承basic_variable_traits
 * @pointer_type: 变量的指针类型
 * @class_type: 成员变量的类类型
 */
template <typename T>
struct variable_traits;

template <typename T>
struct variable_traits<T*>
  :public internal::basic_variable_traits<T>
{
  using pointer_type = T*;
};

template <typename Class, typename T>
struct variable_traits<T (Class::*)>
  :public internal::basic_variable_traits<T (Class::*)>
{
  using pointer_type = T (Class::*);
  using class_type = Class;
};

#endif // #ifndef
