#ifndef RANGE_HPP
#define RANGE_HPP
#include "common-header.hpp"


template <class first, class last>
struct make_iter_range
    :mpl::copy<
        mpl::iterator_range<first, last>,
        mpl::back_inserter<mpl::vector<> >
     >
{};

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

typedef mpl::transform<
            make_iter_range<first, last>::type,
            mpl::deref<_1>
        >::type elements;

static_assert(
        mpl::equal<
            vec,
            elements
        >::value, 
        "equal");
}/* end of anonymous namespace */

#endif
