#include "common-header.hpp"
#include "range.hpp"

template <class Seq>
struct double_first_half {
    typedef 
        typename mpl::divides<
            typename mpl::size<Seq>::type,
            mpl::int_<2>
        >::type last;

    typedef typename 
    mpl::transform< 
        typename make_range<0, mpl::size<Seq>::value>::type,
        mpl::eval_if<
            mpl::less<_1, last>,
            mpl::multiplies<
                mpl::at<Seq, _1>,
                mpl::int_<2>
            >,
            mpl::at<Seq, _1>
         >
    >::type type;
};

static_assert(
        mpl::equal<
            double_first_half<mpl::vector_c<int, 1, 2, 3, 4> >::type,
            mpl::vector_c<int, 2, 4, 3, 4>
        >::value,
        "equal");

