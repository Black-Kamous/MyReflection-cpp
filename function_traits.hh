#ifndef FUNCTION_TRAITS_HH
#define FUNCTION_TRAITS_HH

#include <tuple>
#include <type_traits>

namespace internal{

template <typename T>
struct basic_function_traits;

/**
 * 记录函数类型萃取的通用信息
 * @return_type: 函数返回类型 
 */
template <typename Ret, typename ...Params>
struct basic_function_traits<Ret(Params&&...)>
{
    using return_type = Ret;
};

/**
 * 判断一个类型是否函数（成员&非成员）
 */
template <typename T>
struct is_function
{
  static constexpr bool value = std::is_function<std::remove_pointer<T>>::value ||
    std::is_member_function_pointer<T>::value;
};
  
}

/**
 * 函数类型萃取，继承basic_function_traits，为非成员函数，
 * 成员函数，常量成员函数提供了不同的偏特化
 * 
 * @type: 函数指针类型
 * @params: 函数参数类型tuple
 * @is_member: 是否成员函数
 * @is_const: 是否常量成员函数 
 */
template <typename T>
struct function_traits;

template <typename Ret, typename ...Params>
struct function_traits<Ret(*)(Params...)>
    : internal::basic_function_traits<Ret(Params...)>
{
    using type = Ret(*)(Params...);
    using params = std::tuple<Params...>;
    static constexpr bool is_member = false;
    static constexpr bool is_const = false;
};

template <typename Ret, typename Class, typename ...Params>
struct function_traits<Ret(Class::*)(Params...)>
    : internal::basic_function_traits<Ret(Params...)>
{
    using type = Ret(Class::*)(Params...);
    using params = std::tuple<Class*, Params...>;
    static constexpr bool is_member = true;
    static constexpr bool is_const = false;
};

template <typename Ret, typename Class, typename ...Params>
struct function_traits<Ret(Class::*)(Params...) const>
    : internal::basic_function_traits<Ret(Params...)>
{
    using type = Ret(Class::*)(Params...) const;
    using params = std::tuple<Class*, Params...>;
    static constexpr bool is_member = true;
    static constexpr bool is_const = true;
};

/**
 * is_function的包装函数
 * @return 是否函数
 */
template <typename T>
constexpr bool is_function_v = internal::is_function<T>::value;

#endif //ifndef
