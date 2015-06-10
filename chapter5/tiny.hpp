#include "common-header.hpp"
#include <boost/mpl/iterator_tags.hpp>

struct none {};

struct tiny_tag {};

template <class T0 = none,
          class T1 = none,
          class T2 = none,
          class T3 = none
          >
struct tiny {
    typedef tiny type;
    typedef tiny_tag tag;
    typedef T0 t0;
    typedef T1 t1;
    typedef T2 t2;
    typedef T3 t3;
};

template <class Tiny, class Pos>
struct tiny_iterator {
    typedef mpl::random_access_iterator_tag category;
};

template <class Tiny, class Pos>
struct next<tiny_iterator<Tiny, Pos> > {
    typedef tiny_iterator<Tiny, typename mpl::next<Pos>::type> type;
};

template <class Tiny, class Pos>
struct prior<tiny_iterator<Tiny, Pos> > {
    typedef tiny_iterator<Tiny, typename mpl::prior<Pos>::type> type;
};

template <class Tiny, int N>
struct tiny_at;

template <class Tiny>
struct tiny_at{};

template <class Tiny>
struct tiny_at {
    typedef typename Tiny::t0 type;
};

template <class Tiny>
struct tiny_at {
    typedef typename Tiny::t1 type;
};

template <class Tiny>
struct tiny_at {
    typedef typename Tiny::t2 type;
};

template <class Tiny>
struct tiny_at {
    typedef typename Tiny::t3 type;
};

template <class T0, class T1, class T2, class T3, class Pos>
struct at<tiny<T0, T1, T2, T3>, Pos>
    : tiny_at<tiny<T0, T1, T2, T3>, Pos::value> {
};

template <>
struct at_impl<tiny_tag> {
    template <class Tiny, class N>
    struct apply: tiny_at<Tiny, N::value> {};
};

template <class Tiny, class Pos>
struct deref<tiny_iterator<Tiny, Pos> > 
    : at<Tiny, Pos> {
};

template <class Tiny, class Pos, class N>
struct advance<tiny_iterator<Tiny, Pos>, N> {
    typedef tiny_iterator<Tiny, typename mpl::plus<Pos, N>:type> type;
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

template <class T0, class T1, class T2, class T3>
struct tiny_size 
    : mpl::int_<4> {
};

template <class T0, class T1, class T2>
struct tiny_size<T0, T1, T2, none>
    : mpl::int_<3> {
};

template <class T0, class T1>
struct tiny_size<T0, T1, none, none>
    : mpl::int_<2> {
};

template <class T0>
struct tiny_size<T0, none, none, none>
    : mpl::int_<1> {
};

template <>
struct tiny_size<none, none, none, none>
    : mpl::int_<0> {
};

template <>
struct end_impl<tiny_tag> {
    template <class Tiny>
    struct apply {
        typedef tiny_iterator<
                Tiny,
                typename tiny_size<
                        typename Tiny::t0,
                        typename Tiny::t1,
                        typename Tiny::t2,
                        typename Tiny::t3
                        >::type
                >  type;
    };
};

