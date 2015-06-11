#ifndef EVAL_HPP
#define EVAL_HPP
#include "common-header.hpp"

template <class T>
struct param_type: mpl::eval_if< 
                   std::is_scalar<T>,
                   mpl::identity<T>,
                   std::add_lvalue_reference<const T>> {
                   };

/**
 * Is there any difference between forwarding and nested.
 */

template <class Cond, class Then, class Else>
struct eval_if3 
    :mpl::if_<Cond, typename Then::type, typename Else::type>
{};

template <class Cond, class Then, class Else>
struct eval_if4 {
    typedef typename mpl::if_<Cond, typename Then::type, typename Else::type>::type  type;
};

/**
 * Lazy version.
 */
template <class Cond, class Then, class Else>
struct eval_if1
    : mpl::if_<Cond, Then, Else>::type {};

template <class Cond, class Then, class Else>
struct eval_if2 {
    typedef typename mpl::if_<Cond, Then, Else>::type res;
    typedef typename res::type type;
};

using mpl::true_;
using mpl::false_;

static_assert(
        std::is_same<
            eval_if3<true_, mpl::identity<int>, mpl::identity<long>>::type, 
            eval_if4<true_, mpl::identity<int>, mpl::identity<long>>::type
        >::value, "case 0");

static_assert(
        std::is_same<
            eval_if1<true_, mpl::identity<int>, mpl::identity<long>>::type, 
            eval_if2<true_, mpl::identity<int>, mpl::identity<long>>::type
        >::value, "case 1");

static_assert(
        std::is_same<
            mpl::if_<true_, int, long>::type,
            int
        >::value, "case 2");

/* main */
static_assert(std::is_same<int, param_type<int>::type>::value, "int");
static_assert(std::is_same<const std::string&, param_type<std::string>::type>::value, "string");

#endif
