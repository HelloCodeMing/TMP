#include "common-header.hpp"

typedef mpl::vector<short, int, long, unsigned long> types;
typedef mpl::find<types, long>::type long_pos;
typedef mpl::deref<long_pos>::type long_type;
static_assert(std::is_same<long_type, long>::value, "deref");

