#include <predef.hpp>


template <class T>
struct add_const_ref {
    typedef const T& type;
};

template <class T>
struct add_const_ref<T&> {
    typedef T type;
};

template <class T>
struct add_ref {
    typedef T& type;
};

template <class T>
struct add_ref<T&> {
    typedef T type;
};

int main()
{
    constexpr bool is_same = std::is_same<add_const_ref<int&>::type, add_const_ref<int>::type>::value;
    assert(is_same);
    return 0;
}
