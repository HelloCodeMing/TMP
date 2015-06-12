#include "common-header.hpp"

template <class T, class N>
struct extent
    :std::extent<T, N::value> {
};
