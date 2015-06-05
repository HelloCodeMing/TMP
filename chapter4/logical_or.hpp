#include "common-header.hpp"

using mpl::true_;
using mpl::false_;

template <class Cond, class ThenFunc, class ElseFunc>
struct if_ { 
};

template <class ThenFunc, class ElseFunc>
struct if_<true_, ThenFunc, ElseFunc> {
    typedef typename ThenFunc::type type;
};

template <class ThenFunc, class ElseFunc>
struct if_<false_, ThenFunc, ElseFunc> {
    typedef typename ElseFunc::type type;
};

template <class Cond, class ThenFunc, class ElseFunc> 
struct eval_if:  if_<Cond, ThenFunc, ElseFunc>::type {
};

template <class ...Arg> struct logical_or {};

template <>
struct logical_or<> {
    typedef false_ type;
    static const bool value = false;
};


template <class Head, class ...Tail>
struct logical_or<Head, Tail...> {
    typedef typename eval_if< Head,
                          true_,
                          logical_or<Tail...>
                        >::type type;
    static const bool value = true;
};


/**
 * test cases, using short circuit characteristic.
 */

/**
 * Has no member "type", so will crash when instantied.
 */
template <class T>
struct Boom {
};

/* The or_ */
static_assert(mpl::or_< true_,
                        mpl::identity<int&>,
                        Boom<int> 
                        >::value, "short circuit or boom");

static_assert(std::is_same< 
                mpl::or_< true_, false_>::type, 
                true_>::value, "true_ and false_");

static_assert(std::is_same<
                mpl::or_< false_, true_>::type,
                true_>::value, "false_ and true_");

static_assert(std::is_same<
                mpl::or_< false_, false_>::type,
                false_>::value, "true_ and true_");

/* logical or */
static_assert(logical_or< true_,
                          Boom<int>
                        >::value, "short circuit or boom");

static_assert(std::is_same<
                logical_or< true_, false_>::type,
                true_>::value, "true_ and false_");

static_assert(std::is_same<
                logical_or< false_, true_>::type,
                true_>::value, "false_ and true_");

static_assert(std::is_same<
                logical_or< false_, false_>::type,
                false_>::value, "false_ and false_");

static_assert(std::is_same<
                logical_or< false_, false_, false_, true_>::type,
                true_>::value, "false_ ,false_, false_, true_");

static_assert(std::is_same<
                logical_or< false_, false_, false_, false_>::type,
                false_>::value, "false_, false_, false_, false_");
