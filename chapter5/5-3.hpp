#include "common-header.hpp"
#include "slice.hpp"

struct tiny_tag{};
template <class IteratorTag> struct insert_impl;

template <>
struct insert_impl<tiny_tag> {
    template <class Tiny, class pos, class T>
    struct apply {
        typedef typename slice<typename mpl::begin<Tiny>::type, pos>::type first_part;
        typedef typename slice<pos, typename mpl::end<Tiny>::type >::type last_part;
        typedef 
        typename mpl::copy<
                    last_part,
                    mpl::back_inserter<
                        typename mpl::push_back<first_part, T>::type
                    >
                >::type type;
     };
};


/**
 * Test.
 */
namespace test_5_3{
typedef mpl::vector_c<int, 1, 2, 3> vec;
typedef mpl::apply<
            insert_impl<tiny_tag>, 
            vec, 
            mpl::begin<vec>::type, 
            mpl::int_<4> 
        >::type vec1;

static_assert(
        mpl::front<vec1>::type::value == 4,
        "insert impl");

typedef mpl::apply<
            insert_impl<tiny_tag>,
            vec,
            mpl::next<mpl::begin<vec>::type >::type,
            mpl::int_<4>
        >::type vec2;

static_assert(
        mpl::at<vec2, mpl::int_<1> >::type::value == 4,
        "insert impl 2");
}/* end of test_5_3 namespace */
