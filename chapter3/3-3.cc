#include "common-header.hpp"
#include "twice.hpp"

template <class T>
struct quartic_pointer
    : twice<std::add_pointer<_1>, typename twice<std::add_pointer<_1>, T>::type> {
    };


template <class Fn, class Arg>
struct quartic
    : twice<Fn, typename twice<Fn, Arg>::type> {
    };

int main()
{
    typedef typename std::add_pointer<int>::type once;
    typedef typename std::add_pointer<once>::type pp;
    static_assert(std::is_same<once, int*>::value, "pointer");
    static_assert(std::is_same<pp, int**>::value, "pointer to pointer ?");

    typedef typename twice<std::add_pointer<_1>, int>::type pp2;
    static_assert(std::is_same<pp, int**>::value, "pointer to pointer ?");

    static_assert(std::is_same<typename quartic_pointer<int>::type, int****>::value, "int****");
    static_assert(std::is_same<typename quartic<std::add_pointer<_1>, int>::type, int****>::value, "int****");

    return 0;
}
