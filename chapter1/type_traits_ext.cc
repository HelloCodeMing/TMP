#include <type_traits>
#include <cassert>

/* is_same metafunction */
template <class T1, class T2>
struct is_same {
    const static bool value = false;
};

template <class T1>
struct is_same<T1, T1> {
    const static bool value = true;
};

/* make_unsigned family */
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

/* result of a function */
template <class Fn>
struct result_of {
    typedef Ret type;
};

template <class Ret, class Arg>
struct result_of<Ret(Arg)> {
    typedef Ret type;
};

int main()
{
    bool same = is_same<unsigned int, typename make_unsigned<int>::type>::value;
    assert(same);
    same = is_same<int*, typename result_of<int*(char&)>::type>::value;
    assert(same);
    same = is_same<int*, typename result_of<int&(char*)>::type>::value;
    assert(same == false);
    return 0;
}
