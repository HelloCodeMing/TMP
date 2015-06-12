#ifndef SPLICE_HPP
#define SPLICE_HPP
#include "common-header.hpp"

template <class LHS, class RHS> 
struct splice 
    :mpl::copy<
        RHS,
        mpl::back_inserter<LHS>
    > {
};

namespace test_splice {

typedef mpl::vector<short, int> vec1;
typedef mpl::vector<unsigned, long> vec2;
typedef mpl::vector<short, int, unsigned, long> vec3;

static_assert(
        mpl::equal<
            splice<vec1, vec2>::type,
            vec3
        >::value,
        "splice");
}/* end of namespace test_splice */
#endif
