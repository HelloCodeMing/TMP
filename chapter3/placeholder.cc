#include <vector>
#include <iostream>

#include <boost/lambda/lambda.hpp>

using namespace boost::lambda;

template <int N> arg;

template <>
struct arg<1> {
    friend int operator + (int rhs) {
    }
};

int main()
{
    std::vector<int> vec = {1, 2, 3};
    std::transform(vec.begin(), vec.end(), vec.begin(), _1 + 2);
    for (auto i: vec) std::cout << i << std::endl;
    return 0;
}
