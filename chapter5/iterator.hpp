#include "common-header.hpp"

typedef mpl::vector<short, int, long, unsigned long> types;
typedef mpl::find<types, long>::type long_pos;

static_assert(std::is_same<mpl::deref<long_pos>::type, long>::value, "deref");
typedef mpl::next<long_pos>::type ul_pos;
static_assert(std::is_same<mpl::deref<ul_pos>::type, unsigned long>::value, "next");

/**
 * Implementation of deref.
 */

template <class Iterator>
struct deref{
    typedef typename Iterator::type type;
};

/**
 * Implementation of next.
 */
template <class Iterator>
struct next{
    typedef typename Iterator::next type;
};

static_assert(std::is_same<deref<long_pos>::type, long>::value, "deref");
static_assert(std::is_same<deref<ul_pos>::type, unsigned long>::value, "next");
