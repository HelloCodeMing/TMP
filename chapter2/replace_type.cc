#include <predef.hpp>

template <class T1, class T2, class T3>
struct replace_type { 
    typedef T3 type;
};

/* T1 is pointer */
template <class T1, class T2, class T3>
struct replace_type<T1*, T2, T3> {
    typedef T3* type;
};

/* T1 is function pointer, argument type is same with T2. */
template <class T1, class T2, class T3>
struct replace_type<T1(*)(T2), T2, T3> {
    typedef T1 (*type)(T3) ;
};

/* T1 is function pointer, return type is same with T2. */
template <class T1, class T2, class T3>
struct replace_type<T2(*)(T1), T2, T3> {
    typedef T3 (*type)(T1);
};

/* T1 is function pointer, both argument type and return type is same with T2. */
template <class T2, class T3>
struct replace_type<T2(*)(T2), T2, T3> {
    typedef T3 (*type)(T3);
};

/* T1 is array */
template <class T1, class T2, class T3>
struct replace_type<T1[], T2, T3> {
    typedef T3 type[];
};

/* T1 is an array with fixed length */
template <class T1, class T2, class T3, size_t n>
struct replace_type<T1*[n], T2, T3> {
    typedef T3* type[n];
};

/* T1 is reference */
template <class T1, class T2, class T3>
struct replace_type<T1&, T2, T3> {
    typedef T3& type;
};

int main()
{
    bool is_same = std::is_same<replace_type<void*, void, int>::type, int*>::value;
    assert(is_same);
    is_same = std::is_same<replace_type<int[], int, long>::type, long[]>::value;
    assert(is_same);

    is_same = std::is_same<replace_type<int const*[10], int const, long>::type, long*[10]>::value;
    assert(is_same);

    is_same = std::is_same<replace_type<char& (*)(char&), char&, long&>::type, long& (*)(long&)>::value;
    assert(is_same);

    is_same = std::is_same<replace_type<int* (*)(double), double, int&>::type, int* (*)(int&)>::value;
    assert(is_same);

    is_same = std::is_same<replace_type<int* (*)(double), int*, double*>::type, double*(*)(double)>::value;
    assert(is_same);
    return 0;
}
