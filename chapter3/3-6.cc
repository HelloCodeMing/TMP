#include <iostream>
#include "common-header.hpp"

template <class Fn, class Arg>
struct twice: mpl::apply<Fn, typename mpl::apply<Fn, Arg>::type> {
};

struct twice2: mpl::apply<_1, typename mpl::apply<_1, _2>::type> {
};

int main()
{
    
    typedef typename mpl::apply<_1, typename mpl::apply<_1, _2>::type>::type twice3;
    static_assert(std::is_same<twice<std::add_pointer<_1>, int>::type, int**>::value, "twice");
    //static_assert(std::is_same<twice2<std::add_pointer<_1>, int>::type, int**>::value, "twice2");
    static_assert(std::is_same<twice2::template apply<std::add_pointer<_1>, int>::type, int**>::value, "shit");
    static_assert(std::is_same<twice3::template apply<std::add_pointer<_1>, int>::type, int**>::value, "shit");
    return 0;
}
