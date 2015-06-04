#include <vector>
#include <iostream>

#include "common-header.hpp"

int main()
{
    /* the metadata itself */
    typedef mpl::lambda<_1>::type t0;
    typedef mpl::lambda<mpl::lambda<_1> >::type t1;
    static_assert(std::is_same<t0::template apply<int>::type, int>::value, "t0");
    static_assert(std::is_same<t1::template apply<int>::type, int>::value, "t1");
    
    /* the second parameter */
    typedef mpl::apply<_1, mpl::plus<_1, _2> >::type t2;
    static_assert(std::is_same<t2, mpl::plus<_1, _2>>::value, "t2");

    typedef mpl::apply<_1, std::vector<int>> ::type t3;
    static_assert(std::is_same<t3, std::vector<int>>::value, "t3");

    typedef mpl::apply<_1, std::vector<_1> >::type t4;
    static_assert(std::is_same<t4, std::vector<_1> >::value, "t4");

    typedef mpl::apply<mpl::lambda<_1>, std::vector<int> >::type t5;
    static_assert(std::is_same<t5, std::vector<int> >::value, "t5");

    /* metafunction class, same as the second parameter */
    typedef mpl::apply<mpl::lambda<_1>, std::vector<_1> >::type t6;
    static_assert(std::is_same<t6::template apply<int>::type, std::vector<int> >::value, "t6");
    
    /* metafunction class, which needs two parameter */
    typedef mpl::apply<mpl::lambda<_1>, mpl::plus<_1, _2> >::type t7;
    static_assert(mpl::plus<mpl::int_<1>, mpl::int_<2> >::type::value == 3, "1+2 =? 3");
    static_assert(t7::template apply<mpl::int_<1>, mpl::int_<2>>::type::value == 3, "t7");

    /* same as the second parameter */
    typedef mpl::apply<_1, mpl::lambda<mpl::plus<_1, _2> > > ::type t8;
    static_assert(t8::type::template apply<mpl::int_<1>, mpl::int_<2>>::type::value == 3, "t8");

    puts("pass all assert!");
    return 0;
}
