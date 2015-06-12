#ifndef TINY_HPP
#define TINY_HPP
#include "common-header.hpp"

struct none {};

struct tiny_tag {};

template <class T0 = none,
          class T1 = none,
          class T2 = none
          >
struct tiny {
    typedef tiny type;
    typedef tiny_tag tag;
    typedef T0 t0;
    typedef T1 t1;
    typedef T2 t2;
};

template <class Tiny, class Pos>
struct tiny_iterator {
    typedef mpl::random_access_iterator_tag category;
    typedef tiny_iterator<Tiny, Pos> type;
};

namespace boost { namespace mpl {

template <class Tiny, class Pos>
struct next<tiny_iterator<Tiny, Pos> > {
    typedef tiny_iterator<Tiny, typename mpl::next<Pos>::type> type;
};

template <class Tiny, class Pos>
struct prior<tiny_iterator<Tiny, Pos> > {
    typedef tiny_iterator<Tiny, typename mpl::prior<Pos>::type> type;
};

}}

template <class Tiny, long N>
struct tiny_at;

template <class Tiny>
struct tiny_at<Tiny, 0> {
    typedef typename Tiny::t0 type;
};

template <class Tiny>
struct tiny_at<Tiny, 1> {
    typedef typename Tiny::t1 type;
};

template <class Tiny>
struct tiny_at<Tiny, 2> {
    typedef typename Tiny::t2 type;
};


namespace boost { namespace mpl {

//template <class T0, class T1, class T2, class Pos>
//struct at<tiny<T0, T1, T2>, Pos>
//    : tiny_at<tiny<T0, T1, T2>, Pos::value> {
//};

template <>
struct at_impl<tiny_tag> {
    template <class Tiny, class N>
    struct apply: tiny_at<Tiny, N::value> {};
};

template <class Tiny, class Pos>
struct deref<tiny_iterator<Tiny, Pos> > 
    : mpl::at<Tiny, Pos> {
};

template <class Tiny, class Pos, class N>
struct advance<tiny_iterator<Tiny, Pos>, N> {
    typedef 
    typename tiny_iterator<
                Tiny, 
                typename mpl::plus<Pos, N>::type
             >::type type;
};

template <class Tiny, class Pos1, class Pos2>
struct distance<
    tiny_iterator<Tiny, Pos1>,
    tiny_iterator<Tiny, Pos2>
    >
    : mpl::minus<Pos2, Pos1>{
};

template <>
struct begin_impl<tiny_tag> {
    template <class Tiny>
    struct apply {
        typedef tiny_iterator<Tiny, mpl::int_<0> > type;
    };
};

}}

template <class T0, class T1, class T2>
struct tiny_size
    : mpl::int_<3> {
};

template <class T0, class T1>
struct tiny_size<T0, T1, none>
    : mpl::int_<2> {
};

template <class T0>
struct tiny_size<T0, none, none>
    : mpl::int_<1> {
};

template <>
struct tiny_size<none, none, none>
    : mpl::int_<0> {
};

namespace boost { namespace mpl {

template <>
struct size_impl<tiny_tag> {
    template <class Tiny>
    struct apply 
        :tiny_size<
            typename Tiny::t0,
            typename Tiny::t1,
            typename Tiny::t2
        > {
    };
};
template <>
struct end_impl<tiny_tag> {
    template <class Tiny>
    struct apply {
        typedef typename tiny_iterator<
                Tiny,
                typename tiny_size<
                        typename Tiny::t0,
                        typename Tiny::t1,
                        typename Tiny::t2
                        >::type
                >::type  type;
    };
};

template <>
struct clear_impl<tiny_tag> {
    template <class Tiny>
    struct apply 
        : tiny<> {
    };
};

template <>
struct push_front_impl<tiny_tag> {
    template <class Tiny, class T>
    struct apply
        : tiny<T, typename Tiny::t0, typename Tiny::t1> {
    };
};

}} /* end of namespace boost::mpl */

template <class Tiny, class T, int Size>
struct tiny_push_back;

template <class Tiny, class T>
struct tiny_push_back<Tiny, T, 0> 
    : tiny<T>{
};

template <class Tiny, class T>
struct tiny_push_back<Tiny, T, 1>
    : tiny<typename Tiny::t0, T> {
};

template <class Tiny, class T>
struct tiny_push_back<Tiny, T, 2>
    : tiny<typename Tiny::t0, typename Tiny::t1, T> {
};

namespace boost { namespace mpl {
template <>
struct push_back_impl<tiny_tag> {
    template <class Tiny, class T>
    struct apply 
        : tiny_push_back<
            Tiny,
            T,
            mpl::size<Tiny>::value
        >{
    };
};
}}/* end of namespace boost::mpl */


namespace test_tiny {
    
typedef tiny<short, unsigned, int> t1;
typedef mpl::deref<mpl::begin<t1>::type>::type head;
static_assert(
        std::is_same<
            head,
            short
        >::value,
        "begin");

typedef mpl::next<mpl::begin<t1>::type>::type body;
static_assert(
        std::is_same<
            mpl::deref<body>::type,
            unsigned
        >::value,
        "next");

/* test for fold */

typedef tiny<mpl::int_<1>, mpl::int_<2>, mpl::int_<3> > t2;
typedef mpl::fold<t2, mpl::int_<0>, mpl::plus<_, _> >::type t3;
static_assert(
        mpl::equal_to<
            t3,
            mpl::int_<6>
        >::value,
        "fold");

/* test for equal */
static_assert(
        mpl::equal<
            t1,
            tiny<short, unsigned, int>
        >::value,
        "equal");

/* test for at */
static_assert(
        std::is_same<
            mpl::at_c<t1, 1>::type,
            unsigned
        >::value,
        "at");
} /* end of namespace test_tiny */
#endif
