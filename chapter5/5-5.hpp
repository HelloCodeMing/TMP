#include "tiny.hpp"
#include "splice.hpp"
#include "slice.hpp"


template <class Tiny, int Size> 
struct tiny_pop_back;

template <class Tiny>
struct tiny_pop_back<Tiny, 1> 
    :tiny<>{
};

template <class Tiny>
struct tiny_pop_back<Tiny, 2>
    :tiny<typename Tiny::t0> {
};

template <class Tiny>
struct tiny_pop_back<Tiny, 3>
    :tiny<typename Tiny::t0, typename Tiny::t1> {
};


template <class Tiny, int Pos>
struct tiny_erase;

template <class Tiny>
struct tiny_erase<Tiny, 0>
    :tiny<
        typename Tiny::t1,
        typename Tiny::t2
    > {
};

template <class Tiny>
struct tiny_erase<Tiny, 1>
    :tiny<
        typename Tiny::t0,
        typename Tiny::t2
    > {
};

template <class Tiny>
struct tiny_erase<Tiny, 2>
    :tiny<
        typename Tiny::t0,
        typename Tiny::t1
    > {
};

namespace boost { namespace mpl {

template <>
struct pop_front_impl<tiny_tag> {
    template <class Tiny>
    struct apply
        :tiny<typename Tiny::t1, typename Tiny::t2> {
    };
};

template <>
struct pop_back_impl<tiny_tag> {
    template <class Tiny>
    struct apply
        :tiny_pop_back<
            Tiny,
            mpl::size<Tiny>::value
         > {
     };
};

template <>
struct erase_impl<tiny_tag> {
    template <class Tiny, class First, class Last>
    struct apply {
        typedef typename mpl::begin<Tiny>::type begin;
        typedef typename mpl::end<Tiny>::type end;
        typedef typename splice<
                    typename slice<begin, First>::type,
                    typename slice<Last, end>::type
                >::type type;
                    
    };
};

}}/* end of namespace boost::mpl */

/**
 * Test for pop_front, pop_back, erase.
 */

namespace test_5_5 {

typedef tiny<short, int, long> t1;
typedef mpl::pop_front<t1>::type t2;
typedef mpl::pop_back<t1>::type t3;
typedef mpl::advance_c<mpl::begin<t1>::type, 1>::type first;
typedef mpl::advance_c<mpl::end<t1>::type, -1>::type last;
typedef mpl::erase<t1, first, last>::type t4;

static_assert(
        mpl::equal<
            t2,
            tiny<int, long>
        >::value,
        "pop_front");

static_assert(
        mpl::equal<
            t3,
            tiny<short, int>
        >::value,
        "pop_back");

static_assert(
        mpl::equal<
            t4,
            tiny<short, long>
        >::value,
        "erase");
} /* end of namespace test_5_5 */
