#ifndef FIELD_TRAITS_HH
#define FIELD_TRAITS_HH

#include "function_traits.hh"
#include "variable_traits.hh"

namespace internal{

/**
 * 记录字段类型萃取基本信息，字段有两种情况：函数和变量。
 * @traits: 函数/变量类型萃取结果
 * @is_member:
 * @is_const:
 * @is_function:
 * @is_variable: 含义直白，略
 */
template <typename T, bool isFunc>
struct basic_field_traits;

template <typename T>
struct basic_field_traits<T, true>
  :public function_traits<T>
{
  using traits = function_traits<T>;

  constexpr bool is_member() {return traits::is_member;}

  constexpr bool is_const() {return traits::is_const;}

  constexpr bool is_function() {return true;}

  constexpr bool is_variable() {return false;}
};

template <typename T>
struct basic_field_traits<T, false>
  :public variable_traits<T>
{
  using traits = variable_traits<T>;

  constexpr bool is_member() {return traits::is_member;}

  constexpr bool is_const() {return traits::is_const;}

  constexpr bool is_function() {return false;}

  constexpr bool is_variable() {return true;}
};
}

/**
 * 字段类型萃取，继承basic_field_traits
 * @pointer: 指向所萃取对象的指针
 * 
 * 本模板类有构造函数，可以通过构造函数自动推断模板参数类型，
 * 同时调用构造函数得到的结果是特例化的对象，若要取得类型萃
 * 取相关信息需要进一步操作 //TODO
 */
template <typename T>
struct field_traits
  : public internal::basic_field_traits<T, is_function_v<T>>
{
  constexpr field_traits(T&& p):pointer{p}{}
  T pointer;
};

#endif // #ifndef
