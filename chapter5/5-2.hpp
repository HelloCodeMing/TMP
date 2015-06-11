#include "common-header.hpp"

template <>
struct push_front_impl<tiny_tag> {
    template <class Tiny, class T>
    struct apply
        :tiny<T, typename Tiny::t0, typename Tiny::t1> {
        static_assert(mpl::less<mpl::size<Tiny>::type, mpl::int_<3> >::value, "no empty place left!");
    };
};
