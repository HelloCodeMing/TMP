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
    typedef typename mpl::lambda<
                        mpl::apply<_1, 
                            typename mpl::apply<_1, _2>::type
                                >::type
                                    >::type twice3;
    typedef typename mpl::lambda<_1::template apply<_1::template apply<_2>::type>::type>::type twice4;
    
    static_assert(std::is_same<twice<std::add_pointer<_1>, int>::type, int**>::value, "twice");
    
    static_assert(std::is_same<mpl::apply<twice2, std::add_pointer<_1>, int>::type, int**>::value, "metafunction class");
    static_assert(std::is_same<mpl::apply<twice3, std::add_pointer<_1>, int>::type, int**>::value, "placeholder expression");
    static_assert(std::is_same<mpl::apply<twice4, std::add_pointer<_1>, int>::type, int**>::value, "placeholder expression");
    return 0;
}
