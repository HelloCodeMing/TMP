#include "common-header.hpp"


/**
 * If this template is instantied with a referencel, it will crash, 
 * because there's no pointer to reference in C++.
 */
template <class T>
struct Boom {
    //typedef T* type;
    //typedef mpl::true_ value;
};

static_assert(std::is_same<int, 
                            mpl::if_<
                            mpl::or_< mpl::true_, Boom<int&>>,
                            int,
                            int&>::type>::value, 
                            "or");
static_assert(std::is_same<int,
                            mpl::if_<
                            mpl::and_<mpl::false_, Boom<int&>>,
                            int&, 
                            int>::type>::value,
                            "and");
