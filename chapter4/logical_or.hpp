#include "common-header.hpp"

using mpl::true_;
using mpl::false_;

/**
 * naive version
 */

template <class T1 = false_, class T2 = false_, class T3 = false_>
struct naive_or {
    typedef typename mpl::bool_<T1::type::value || 
                                T2::type::value || 
                                T3::type::value>::type type;
    const static bool value = mpl::bool_<T1::type::value || 
                                         T2::type::value || 
                                         T3::type::value>::value;
};

template <class T1 = false_, class T2 = false_, class T3 = false_>
struct logical_or2 : 
    mpl::eval_if<T1,
    true_,
    logical_or2<T2, T3>> {
};

template <>
struct logical_or2<> : false_ {};

/**
 * Robust version.
 */
template <class Cond, class ThenFunc, class ElseFunc>
struct if_ { 
};

template <class ThenFunc, class ElseFunc>
struct if_<true_, ThenFunc, ElseFunc>: ThenFunc {
};

template <class ThenFunc, class ElseFunc>
struct if_<false_, ThenFunc, ElseFunc>: ElseFunc {
};

template <class Cond, class ThenFunc, class ElseFunc> 
struct eval_if:  if_<Cond, ThenFunc, ElseFunc>::type {
};

template <class ...Arg> struct logical_or {};

template <>
struct logical_or<> : false_ {
};


template <class Head, class ...Tail>
struct logical_or<Head, Tail...> :
    eval_if< Head, true_, logical_or<Tail...>> {
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

static_assert(logical_or2<true_, Boom<int>>::type::value, "short circult or boom");
static_assert(std::is_same<
                logical_or2<false_, false_, false_>::type, 
                false_>::value, "false_, false_, false_");
