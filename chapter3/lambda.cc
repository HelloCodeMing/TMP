#include <type_traits>

template <int N> struct arg;
struct void_;

template <>
struct arg<1> {
    template <class A1, class ...Am>
        struct apply {
            typedef A1 type;
        };
};

typedef arg<1> _1;

template <>
struct arg<2> {
    template <class A1, class A2, class ...Am>
        struct apply {
            typedef A2 type;
        };
};
typedef arg<2> _2;

int main()
{
    static_assert(std::is_same<typename _1::apply<int, void>::type, int>::value, "_1");
    static_assert(std::is_same<_2::apply<int, char*>::type, char*>::value, "_2");
    return 0;
}
