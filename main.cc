#include <type_traits>
#include <iostream>
#include "function_traits.hh"
#include "variable_traits.hh"
#include "field_traits.hh"

class Animal
{
public:
    int legs(){return 0;}
    int eyes(){return 0;}
    int hasFur(int){return 0;}
    int constFunc() const {return 2;}
    float length;
};

int LegsOfAnimal(Animal a)
{
    return 0;
}

int main()
{
    using a = decltype(&Animal::length);
    using b = function_traits<decltype(&Animal::constFunc)>;

    static_assert(b::is_const == true);

    auto c = field_traits{&Animal::constFunc};

    return 0;
}
