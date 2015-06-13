#include "common-header.hpp"
#include "range.hpp"
#include "extent.hpp"

struct dimensions_tag;

template <class T>
struct dimensions {
    typedef dimensions_tag tag;
    typedef dimensions type;
    typedef T value;
    typedef
    typename mpl::reverse_transform<
                typename make_range<0, std::rank<T>::value >::type,
                extent<T, _1>
            >::type detail;
};

template <class D, class Pos>
struct dimensions_iterator {
    typedef mpl::bidirectional_iterator_tag category;
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
    template <class D, class Pos>
    struct apply
        :mpl::at<typename D::detail, Pos> {
    };
};

template <class D, class Pos>
struct deref<dimensions_iterator<D, Pos> > 
    :mpl::at<D, Pos> {
};

template <>
struct begin_impl<dimensions_tag> {
    template <class Dimensions>
    struct apply
        :dimensions_iterator<Dimensions, mpl::int_<0> > {
    };
};

template <>
struct end_impl<dimensions_tag> {
    template <class Dimensions>
    struct apply
        :dimensions_iterator<Dimensions, mpl::size<Dimensions> > {
    };
};

template <class D, class Pos>
struct next<dimensions_iterator<D, Pos> > 
    :dimensions_iterator<D, typename mpl::next<Pos>::type> {
};

template <class D, class Pos>
struct prior<dimensions_iterator<D, Pos> >
    :dimensions_iterator<D, typename mpl::prior<Pos>::type> {
};

template <>
struct clear_impl<dimensions_tag> {
    template <class Dimensions>
    struct apply
        :dimensions<char > {
    };
};



template <>
struct push_front_impl<dimensions_tag> {
    template <class Dimensions, class T>
    struct apply
        :dimensions<typename Dimensions::value[T::value]> {
    };
};

template <>
struct push_back_impl<dimensions_tag> {
    template <class Dimensions, class T>
    struct apply {
        typedef typename mpl::reverse<Dimensions>::type::value reversed_value;
        typedef reversed_value reversed_type[T::value];
        typedef typename mpl::reverse<dimensions<reversed_type> >::type type;
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

typedef mpl::push_back<seq, mpl::int_<1> >::type seq2;
static_assert(
        mpl::equal<
            seq2::detail,
            dimensions<char [10][5][2][1]>::detail
        >::value,
        "push_back equal");
}/* end of namespace test_dimensions */

