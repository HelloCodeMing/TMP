#include "common-header.hpp"


struct fib_tag;

template <size_t Size = 0>
struct fib {
    typedef fib_tag tag;
};

template <size_t N, size_t Prior>
struct fib_iterator {
    typedef mpl::forward_iterator_tag category;
    typedef fib_iterator type;
};

namespace boost { namespace mpl {

template <>
struct begin_impl<fib_tag> {
    template <class F>
    struct apply {
        typedef fib_iterator<0, 1> type;
    };
};

template <>
struct end_impl<fib_tag> {
    template <class F>
    struct apply {
        typedef typename mpl::advance<
                    typename mpl::begin<F>::type, 
                    typename mpl::size<F>::type 
                >::type type;
    };
};

template <size_t N, size_t Prior>
struct next<fib_iterator<N, Prior> > {
    typedef fib_iterator<N+Prior, N> type;
};

template <size_t N, size_t Prior>
struct prior<fib_iterator<N, Prior> > {
    typedef fib_iterator<Prior, N-Prior> type;
};

template <size_t N, size_t Prior>
struct deref<fib_iterator<N, Prior> > 
    :mpl::int_<N> {
};

template <size_t Size>
struct back<fib<Size> > 
    :mpl::deref<
        typename mpl::prior< 
            typename mpl::end<fib<Size>>::type
        >::type
    > {
};

template <size_t Size>
struct size<fib<Size> > 
    :mpl::int_<Size> {
};

}} /* end of namespace boost::mpl */


namespace test_5_8 {

typedef mpl::advance_c<mpl::begin<fib<>>::type, 6>::type p;
static_assert(
        mpl::deref<p>::type::value == 8,
        "advance 6");

typedef fib<8> seq;

static_assert(
        mpl::size<seq>::value == 8,
        "size");

static_assert(
        mpl::back<seq>::type::value == 13,
        "back");

} /* end of namespace test_5_8 */
