#ifndef PUSH_BACK_HPP
#define PUSH_BACK_HPP
#include "common-header.hpp"

template <class Tiny, class T, int N>
struct tiny_push_back;

template <class Tiny, class T>
struct tiny_push_back<0>
    :tiny<T, none, none>{
};

template <class Tiny, class T>
struct tiny_push_back<1>
    :tiny<Tiny::t0, T, none> {
};

template <class Tiny, class T>
struct tiny_push_back<2>
    :tiny<Tiny::t0, Tiny::t1, T> {
};

template <>
struct push_back_impl<tiny_tag> {
    template <class Tiny, class T>
    struct apply
        :tiny_push_back<
            Tiny, T, mpl::size<Tiny>::value
         > {
    };
};

#endif
