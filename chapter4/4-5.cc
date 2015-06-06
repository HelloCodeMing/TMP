#include <vector>
#include <algorithm>
#include <iostream>

#include "common-header.hpp"

template <class Container>
struct iterator_type
    : mpl::if_<
        std::is_const<Container>,
        typename Container::const_iterator,
        typename Container::iterator> {
        };

static_assert(std::is_same<
                iterator_type<const std::vector<int> >::type,
                std::vector<int>::const_iterator
                >::value, "const iterator");

static_assert(std::is_same<
                iterator_type<std::vector<int> >::type,
                std::vector<int>::iterator
                >::value, "iterator");

template <class Container, class value_type>
typename iterator_type<Container>::type
container_find(Container& c, const value_type& v) {
    return std::find(c.begin(), c.end(), v);
}

int main()
{
    std::vector<int> vec = {1, 2, 3};
    container_find(vec, 1);

    const std::vector<int> vec_const = {1, 2, 3};
    container_find(vec_const, 1);
    return 0;
}
