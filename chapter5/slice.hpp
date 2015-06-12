#ifndef SLICE_HPP
#define SLICE_HPP
#include "common-header.hpp"

/**
 * Slice by iterator.
 */
template <class first, class last>
struct slice 
    :mpl::copy<
        mpl::iterator_range<first, last>,
        mpl::back_inserter<mpl::vector<> >
    > {
};

/**
 * Slice by index.
 */
template <class Seq, int first, int last>
struct slice_c {
    typedef typename mpl::advance_c<typename mpl::begin<Seq>::type, first>::type begin;
    typedef typename mpl::advance_c<typename mpl::begin<Seq>::type, last>::type end;
    typedef typename slice<begin, end>::type type;
};


/**
 * Test.
 */

namespace slice_test {

typedef mpl::vector_c<int, 1, 2, 3, 4> vec;
typedef mpl::vector_c<int, 2, 3> part_vec;

static_assert(
        mpl::equal<
            part_vec,
            slice_c<vec, 1, 3>::type
        >::value, 
        "slice by index");

static_assert(
        mpl::equal<
            part_vec,
            slice<
                mpl::next<
                    mpl::begin<vec>::type
                >::type, 
                mpl::prior<
                    mpl::end<vec>::type
                >::type 
            >::type
        >::value,
        "slice by iterator");
/* test transform */

typedef mpl::advance_c<mpl::begin<vec>::type, 1>::type first;
typedef mpl::advance_c<mpl::end<vec>::type, -1>::type last;
static_assert(
        mpl::equal<
            mpl::vector_c<int, 3, 4>,
            mpl::transform<
                slice<first, last>::type,
                mpl::plus<_, mpl::int_<1>>
            >::type
        >::value, 
        "transform or not");



}/* end of slice_test namespace */

#endif
