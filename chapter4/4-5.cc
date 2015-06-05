#include <vector>
#include <algorithm>
#include <iostream>

#include "common-header.hpp"

template <class Container>
struct iterator_type
    : mpl::if_<
        std::is_const<Container>,
        typename Container::iterator,
        const typename Container::iterator> {
          };

template <class Container, class value_type>
typename iterator_type<Container>::type
//typename Container::iterator
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
