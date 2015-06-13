#include "common-header.hpp"

template <class LHS, class RHS>
struct less 
    :mpl::if_c<
        sizeof(LHS) < sizeof(RHS),
        LHS,
        RHS
     > {
};


template <class Seq>
struct smallest 
    :mpl::copy<Seq, mpl::inserter<mpl::void_, less<_, _>> > {
};

namespace test_6_0 {

static_assert(
        std::is_same<
            smallest<mpl::vector<int[2], char, double&> >::type,
            char
        >::value,
        "smallest");

} /* end of namespace test_6_0 */
