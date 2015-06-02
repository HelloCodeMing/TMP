#include <predef.hpp>

template <class T1, class T2, class T3>
struct replace_type { 
    typedef T1 type;
};

/* T1 is pointer */
template <class T1, class T2, class T3>
struct replace_type<T1*, T2, T3> {
    typedef T3* type;
};

/* T1 is pointer, and T2 is reference */
template <class T1, class T2, class T3>
struct replace_type<T1*, T2&, T3&> {
    typedef T3 type;
};

/* T1 is array */
template <class T1, class T2, class T3>
struct replace_type<T1[], T2, T3> {
    typedef T3 type[];
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
    is_same = std::is_same<replace_type<int const*[10], int const, long>::type, long*[10]>::value;
    assert(is_same);
    is_same = std::is_same<replace_type<char& (*)(char&), char&, long&>::type, long& (*)(long&)>::value;
    assert(is_same);
    return 0;
}
