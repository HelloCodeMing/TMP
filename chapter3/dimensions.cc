#include <boost/mpl/vector_c.hpp>
#include <boost/mpl/plus.hpp>
#include <boost/mpl/minus.hpp>
#include <boost/mpl/transform.hpp>
#include <boost/mpl/equal.hpp>
#include <boost/mpl/placeholders.hpp>

#include <cassert>

namespace mpl = boost::mpl;
using namespace mpl::placeholders;

typedef mpl::vector_c<int, 1, 0, 0, 0, 0, 0, 0> mass;
typedef mpl::vector_c<int, 0, 1, 0, 0, 0, 0, 0> length;
typedef mpl::vector_c<int, 0, 0, 1, 0, 0, 0, 0> time;
typedef mpl::vector_c<int, 0, 0, 0, 1, 0, 0, 0> charge;
typedef mpl::vector_c<int, 0, 0, 0, 0, 1, 0, 0> temperature;
typedef mpl::vector_c<int, 0, 0, 0, 0, 0, 1, 0> intensity;
typedef mpl::vector_c<int, 0, 0, 0, 0, 0, 0, 1> substance;

/**
 * Wrapper for int
 */
template <int n>
struct Int {
    const static int value = n;
};

template <class T, class Dimensions>
struct quantity {
    explicit quantity(T x): value_(x) {}

    template <class Other>
        quantity(const quantity<T, Other>& rhs): value_(rhs.value()) {
            static_assert(mpl::equal<Other, Dimensions>::value, "They must has same dimensions");
        }
    
    T value() const { return value_; }
    private:
        T value_;
};

template <class T, class D>
quantity<T, D> operator + (const quantity<T,D>& lhs, const quantity<T, D>& rhs) {
    return quantity<T, D>(lhs.value() + rhs.value());
}

template <class T, class D>
quantity<T, D> operator - (const quantity<T, D>& lhs, const quantity<T, D>& rhs) {
    return quantity<T, D>(lhs.value() - rhs.value());
}

/**
 * wrapper for plus
 */
struct plus_f {
    template <class T1, class T2> 
        struct apply: mpl::plus<T1, T2> {};
};


/**
 * wrapper for minus
 */
struct minus_f {
    template <class T1, class T2>
        struct apply: mpl::minus<T1, T2> {};
};

/**
 * operator * overloading, using placeholder to compute type
 */
template <class T, class D1, class D2>
quantity<T, typename mpl::transform<D1, D2, mpl::plus<_1, _2>>::type>
    operator * (const quantity<T, D1>& lhs, const quantity<T, D2>& rhs) {
        typedef typename mpl::transform<D1, D2, mpl::plus<_1, _2>>::type dim;
        return quantity<T, dim>(lhs.value() * rhs.value());
    }

template <class T, class D1, class D2>
quantity<T, typename mpl::transform<D1, D2, mpl::minus<_1, _2>>::type>
    operator / (const quantity<T, D1>& lhs, const quantity<T, D2>& rhs) {
        typedef typename mpl::transform<D1, D2, mpl::minus<_1, _2>>::type dim;
        return quantity<T, dim>(lhs.value() / rhs.value());
    }


int main()
{
    quantity<float, length> la(1.0);
    quantity<float, length> lb(2.0);
    quantity<float, mass> m(1.0);
    
    quantity<float, length> ls = la + lb;
    assert(ls.value() == 3.0 && "la + lb");

    auto res = la * m;

    return 0;
}
