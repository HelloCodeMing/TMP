#ifndef SLICE_HPP
#define SLICE_HPP
#include "common-header.hpp"
#include "range.hpp"


/**
 * Slice by iterator.
 */
template <class first, class last>
struct slice {
    typedef typename make_iter_range<first, last>::type iter_range;
    typedef typename mpl::transform<iter_range, mpl::deref<_1> >::type type;
};

/**
 * Slice by index.
 */
template <class Seq, int first, int last>
struct slice_c {
    typedef typename mpl::advance<typename mpl::begin<Seq>::type, mpl::int_<first>>::type begin;
    typedef typename mpl::advance<typename mpl::begin<Seq>::type, mpl::int_<last>>::type end;
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
}/* end of slice_test namespace */

#endif
