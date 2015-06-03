#include <type_traits>
#include <cassert>

template <class T1, class T2>
struct is_same {
    const static bool value = false;
};

template <class T1>
struct is_same<T1, T1> {
    const static bool value = true;
};

template <class T>
struct make_unsigned {
    typedef T type;
};

template <>
struct make_unsigned<int> {
    typedef unsigned int type;
};

template <>
struct make_unsigned<char> {
    typedef unsigned char type;
};

template <>
struct make_unsigned<long> {
    typedef unsigned long type;
};

int main()
{
    bool same = is_same<unsigned int, typename make_unsigned<int>::type>::value;
    assert(same);
    return 0;
}
