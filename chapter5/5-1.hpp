#include "common-header.hpp"

template <class T>
struct double_first_half {

};

static_assert(
        mpl::equal<
            double_first_half< mpl::vector_c<int, 1, 2, 3, 4> >::type,
            mpl::vector_c<int, 2, 4, 3, 4>
        >::type::value,
        "equal");
