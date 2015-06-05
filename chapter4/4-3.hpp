#include "common-header.hpp"


/**
 * Case 1
 */
template <class N, class Pred>
struct next_if: 
    mpl::if_<typename mpl::apply<Pred, N>::type,
            typename mpl::next<N>::type,
            N > {
};

/**
 * Optimized version
 */
template <class N, class Pred>
struct next_if2: 
    mpl::if_<typename mpl::apply<Pred, N>::type,
            typename mpl::next<N>::type,
            N > {
};

static_assert(std::is_same<
                mpl::lambda<next_if<_1, _2>>::type,
                mpl::lambda<next_if2<_1, _2>>::type>::value, "case 1");
/**
 * Case 2
 */

template <class N1, class N2>
struct formula : mpl::if_<mpl::not_equal_to<N1, N2>,
                          typename mpl::if_<
                              mpl::greater<N1, N2>,
                              typename mpl::minus<N1, N2>::type,
                              N1>::type,
                          typename mpl::plus<N1, 
                             typename mpl::multiplies<N1, mpl::int_<2>>::type
                          >::type
                         >::type {
};

/**
 * Optimized.
 */
template <class N1, class N2>
struct formula2: mpl::eval_if<mpl::equal_to<N1, N2>,
                     mpl::plus<N1, typename mpl::multiplies<N1, mpl::int_<2>>::type>,
                     mpl::eval_if<mpl::greater<N1, N2>,
                          mpl::minus<N1, N2>,
                          N1>
                    > {};

static_assert(std::is_same<
                formula<mpl::int_<2>, mpl::int_<3>>::type,
                formula2<mpl::int_<2>, mpl::int_<3>>::type
                >::value,"case 2");
