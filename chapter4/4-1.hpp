#include "common-header.hpp"

template <class C1, class C2>
struct logical_or {
    const static bool value = (std::is_same<C1, mpl::true_>::value ||
                               std::is_same<C2, mpl::true_>::value);
};

template <class C1, class C2>
struct logical_and {
    const static bool value = (std::is_same<C1, mpl::true_>::value &&
                               std::is_same<C2, mpl::true_>::value);
};

template <class T>
struct Boom {
    typedef T& type;
};

static_assert(std::is_same<int, 
                            mpl::if_<
                            logical_or< mpl::false_, Boom<int&>::type>,
                            int,
                            int&>::type>::value, 
                            "or");
static_assert(std::is_same<int,
                            mpl::if_<
                            logical_and<mpl::false_, Boom<int&>::type>,
                            int&, 
                            int>::type>::value,
                            "and");
