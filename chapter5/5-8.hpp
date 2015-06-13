#include "common-header.hpp"


struct fib_tag;

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

template <size_t N, size_t Prior>
struct next<fib_iterator<N, Prior> > {
    typedef fib_iterator<N+Prior, N> type;
};

template <size_t N, size_t Prior>
struct deref<fib_iterator<N, Prior> > 
    :mpl::int_<N> {
};

}} /* end of namespace boost::mpl */


namespace test_5_8 {

typedef mpl::advance_c<mpl::begin<fib>::type, 6>::type p;
static_assert(
        mpl::deref<p>::type::value == 8,
        "advance 6");

} /* end of namespace test_5_8 */
