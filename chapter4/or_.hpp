#include "common-header.hpp"

template <class T1 = mpl::false_, class T2 = mpl::false_, class T3 = mpl::false_, class T4 = mpl::false_>
struct logical_or {
    typedef mpl::false_ type;
    const static bool value = false;
};

template <class T2, class T3, class T4>
struct logical_or <mpl::true_, T2, T3, T4> {
    typedef mpl::true_ type;
    const static bool value = true;
};

template <class T3, class T4>
struct logical_or <mpl::false_, mpl::true_, T3, T4> {
    typedef mpl::true_ type;
    const static bool value = true;
};

template <class T4>
struct logical_or <mpl::false_, mpl::false_, mpl::true_, T4> {
    typedef mpl::true_ type;
    const static bool value = true;
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

/* The mpl::or_ */
static_assert(mpl::or_< mpl::true_,
                        mpl::identity<int&>,
                        Boom<int> 
                        >::value, "short circuit or boom");

static_assert(std::is_same< 
                mpl::or_< mpl::true_, mpl::false_>::type, 
                mpl::true_>::value, "true_ and false_");

static_assert(std::is_same<
                mpl::or_< mpl::false_, mpl::true_>::type,
                mpl::true_>::value, "false_ and true_");

static_assert(std::is_same<
                mpl::or_< mpl::false_, mpl::false_>::type,
                mpl::false_>::value, "true_ and true_");

/* logical or */
static_assert(logical_or< mpl::true_,
                        Boom<int>
                        >::value, "short circuit or boom");

static_assert(std::is_same<
                logical_or< mpl::true_, mpl::false_>::type,
                mpl::true_>::value, "true_ and false_");

static_assert(std::is_same<
                logical_or< mpl::false_, mpl::true_>::type,
                mpl::true_>::value, "false_ and true_");

static_assert(std::is_same<
                logical_or< mpl::false_, mpl::false_>::type,
                mpl::false_>::value, "false_ and false_");

static_assert(std::is_same<
                logical_or< mpl::false_, mpl::false_, mpl::false_, mpl::true_>::type,
                mpl::false_>::value, "false_ ,false_, false_, true_");

static_assert(std::is_same<
                logical_or< mpl::false_, mpl::false_, mpl::false_, mpl::false_>::type,
                mpl::false_>::value, "false_, false_, false_, false_");
