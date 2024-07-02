#include "../function_traits.hh"
#include "testant_class.hh"

void test_function_traits()
{
  using a = function_traits<decltype(&Testant_Person::name)>;

  using b = function_traits<decltype(&Testant_Person::birthdate)>;

  using c = function_traits<decltype(getPlanet)>;

  static_assert(a::is_const == false);

}
