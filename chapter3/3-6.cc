#include <iostream>
#include "common-header.hpp"

template <class Fn, class Arg>
struct twice: mpl::apply<Fn, typename mpl::apply<Fn, Arg>::type> {
};

struct twice2 {
    template <class Fn, class Arg>
        struct apply: mpl::apply<Fn, typename mpl::apply<Fn, Arg>::type> {
        };
};

int main()
{
    
    static_assert(std::is_same<twice<std::add_pointer<_1>, int>::type, int**>::value, "twice");
    
    static_assert(std::is_same<mpl::apply<twice2, std::add_pointer<_1>, int>::type, int**>::value, "shit");
    return 0;
}
