#include "common-header.hpp"
#include "range.hpp"
#include "extent.hpp"

struct dimensions_tag;

template <class T>
struct dimensions {
    typedef dimensions_tag tag;
    typedef dimensions<T> type;
    typedef T value;
    typedef
    typename mpl::reverse_transform<
                typename make_range<0, std::rank<T>::value >::type,
                extent<T, _1>
            >::type detail;
};

namespace boost { namespace mpl {

template <>
struct size_impl<dimensions_tag> {
    template <class Dimensions>
    struct apply
        :mpl::size<typename Dimensions::detail> {
    };
};

template <>
struct at_impl<dimensions_tag> {
    template <class Dimensions, class Pos>
    struct apply
        :mpl::at<typename Dimensions::detail, Pos> {
    };
};

template <>
struct push_front_impl<dimensions_tag> {
    template <class Dimensions, class T>
    struct apply
        :dimensions<typename Dimensions::value[T::value]> {
    };
};


}} /* end of namespace boost::mpl */

namespace test_dimensions {

typedef dimensions<char [10][5][2]> seq;

static_assert(
        mpl::size<seq>::value == 3,
        "size");

static_assert(
        mpl::at_c<seq, 0>::type::value == 2,
        "d1");

static_assert(
        mpl::at_c<seq, 1>::type::value == 5,
        "d2");

typedef mpl::push_front<seq, mpl::int_<1> >::type seq1;

static_assert(
        mpl::size<seq1>::value == 4,
        "push_front size");

static_assert(
        mpl::at_c<seq1, 0>::type::value == 2,
        "push_front, at");

static_assert(
        mpl::equal<
            seq1::detail,
            dimensions<char [1][10][5][2]>::detail
        >::value, 
        "push_front, equal");
}/* end of namespace test_dimensions */

