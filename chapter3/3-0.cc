#include <cassert>


template <unsigned long N>
struct binary {
    static_assert(N % 10 == 1 || N % 10 == 0, "Illegal binary");
    const static unsigned value = binary<N/10>::value * 2 + N % 10;
};

template <>
struct binary<0> {
    const static unsigned value = 0;
};

//unsigned binary(unsigned long n) {
//    return n == 0 ? 0 :
//            binary(n / 10) * 2 + n % 10;
//}

int main()
{
    assert((binary<101>::value == 5));
    binary<123>::value;
    //assert(binary(101) == 5);
    return 0;
}
