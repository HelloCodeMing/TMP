#include "common-header.hpp"

struct fib_tag;
struct none;

template <class Pos>
struct fib 
    :mpl::plus<
        typename fib<
            typename mpl::minus<
                Pos,
                mpl::int_<2>
            >::type
        >::value,
        typename fib<
            typename mpl::minus<
                Pos,
                mpl::int_<1>
            >::type
        >::value
    > {
    typedef fib_tag tag;
};

template <>
struct fib<mpl::int_<1> > {
    typedef fib_tag tag;
    typedef fib type;
    typedef mpl::int_<1> value;
};

template <>
struct fib<mpl::int_<2> > {
    typedef fib_tag tag;
    typedef fib type;
    typedef mpl::int_<1> value;
};

template <class Pos>
struct fib_iterator {
    typedef mpl::forward_iterator_tag category;
    typedef fib<Pos> type;
};

namespace boost { namespace mpl {

template <class Pos>
struct deref<fib_iterator<Pos> > {
    typedef typename fib_iterator<Pos>::type type;
};

template <class Pos>
struct next<fib_iterator<Pos> > {
    typedef fib_iterator<typename mpl::next<Pos>::type > type;
};

template <class Pos, class N>
struct advance<fib_iterator<Pos>, N> 
    :fib_iterator<typename mpl::advance<Pos, N>::type> {
};

template <class Pos, int N>
struct advance_c<fib_iterator<Pos>, N>
    :fib_iteartor<typename mpl::advance_c<Pos, N>::type> {
};

template <>
struct begin_impl<fib_tag> {
    template <class F>
    struct apply
        :fib_iterator<mpl::int_<1> > {
    };
};

}} /* end of namepsace boost::mpl */


namespace test_5_8 {

static_assert(fib<mpl::int_<6> >::type::value == 8, "fuck");
//typedef mpl::advance_c<mpl::begin<fib<mpl::int_<1> > >::type, 6>::type p;
//static_assert(mpl::deref<p>::type::value == 8, "advance 6");

} /* end of namespace test_5_8 */
