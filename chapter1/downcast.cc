#include <type_traits>

template <class Target, class Source>
Target down_cast(Source* x) {
    return static_cast<Target>(x);
}

template <class Target, class Source>
Target down_cast(Source& x) {
    return static_cast<Target>(x);
}

struct A { virtual ~A(){} };
struct B : A {};

int main()
{
    B b;
    A* p_a = &b;
    B* p_b = down_cast<B*>(p_a);

    A& r_a = b;
    B& r_b = down_cast<B&>(r_a);
    return 0;
}
