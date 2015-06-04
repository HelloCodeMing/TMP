#include <boost/mpl/plus.hpp>
#include <boost/mpl/int.hpp>
#include <cassert>

using namespace boost::mpl;

/**
 * metafunction class
 */
struct plus_mf {
    template <class T1, class T2> 
        struct apply {
            typedef typename plus<T1, T2>::type type;
        };
};

/**
 * function object(functor)
 */
struct plus_f {
    int operator () (int x, int y) {
        return x + y;
    }
};

/**
 */
template <int lhs, int rhs>
struct plus_ff {
    int operator() () {
        return lhs + rhs;
    }
};

/**
 */
template <int lhs, int rhs>
struct plus_fff {
    const static int value = lhs + rhs;
};

int main()
{
    static_assert((plus<int_<1>, int_<2>>::value == int_<3>::value), "metafunction");
    static_assert((plus_mf::apply<int_<1>, int_<2>>::type::value == int_<3>::value), "metafunction-class");
    assert((plus_f()(1, 2) == 3));
    assert((plus_ff<1, 2>()() == 3));
    static_assert((plus_fff<1, 2>::value == 3), "metafunction2");
    return 0;
}
