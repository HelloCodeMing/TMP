#ifndef SPLICE_HPP
#define SPLICE_HPP
#include "common-header.hpp"

template <class ...Arg>
struct splice;

template <>
struct splice<>
    :mpl::vector<> {
};
    
template <class Head, class ...Tail>
struct splice<Head, Tail...>
    :mpl::copy<
        typename splice<Tail...>::type,
        mpl::back_inserter<Head>
    > {
};

namespace test_splice {

typedef mpl::vector<short, int> vec1;
typedef mpl::vector<unsigned, long> vec2;
typedef mpl::vector<short, int, unsigned, long> vec3;

typedef mpl::vector_c<int, 1, 2, 3> vec4;
typedef mpl::vector_c<int, 4, 5, 6> vec5;
typedef mpl::vector_c<int, 1, 2, 3, 4, 5, 6> vec6;
typedef mpl::vector_c<int, 7, 8, 9> vec7;

static_assert(
        mpl::equal<
            splice<vec1, vec2>::type,
            vec3
        >::value,
        "splice1");

static_assert(
        mpl::equal<
            splice<vec4, vec5>::type,
            vec6
        >::value,
        "splice vector_c");

static_assert(
        mpl::equal<
            splice<
                vec4, vec5, vec7
            >::type,
            mpl::range_c<int, 1, 10>
        >::value,
        "splice tree seqs");

}/* end of namespace test_splice */
#endif
