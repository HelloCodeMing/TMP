#ifndef RANGE_HPP
#define RANGE_HPP
#include "common-header.hpp"

template <int first, int last>
struct make_range
    :mpl::copy<
        mpl::range_c<int, first, last>,
        mpl::back_inserter<mpl::vector<> >
     >
{};

/**
 * Test
 */
namespace range_test {

typedef mpl::vector_c<int, 1, 2, 3, 4> vec;
typedef mpl::begin<vec>::type first;
typedef mpl::end<vec>::type last;

typedef mpl::iterator_range<first, last> elements;

static_assert(
        mpl::equal<
            vec,
            elements
        >::value, 
        "iterator range");

typedef mpl::vector<short, int, long> vec1;

static_assert(
        mpl::equal<
            mpl::iterator_range<
                mpl::begin<vec1>::type,
                mpl::end<vec1>::type
            >,
            vec1
        >::value,
        "iterator_range");

}/* end of anonymous namespace */

#endif
