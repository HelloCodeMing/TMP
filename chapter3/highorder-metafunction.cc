#include <boost/mpl/plus.hpp>

using namespace boost::mpl;

/**
 * compuate F(F(x))
 */
template <class F, class X>
struct twice {
    typedef typename F::template apply<X>::type once;
    typedef typename once::template apply<X>::type type;
};

template <class F, class X>
struct twice1: F::template apply<
              typename F::template apply<X>::type> {};

template <class UnaryMetaFunctionClass, class Arg>
struct apply1 : UnaryMetaFunctionClass::template apply<Arg> {
};

template <class UnaryMetaFunctionClass, class Arg>
struct apply2: apply1<UnaryMetaFunctionClass, typename apply1<UnaryMetaFunctionClass, X>::type> {

};

template <class F, class X>
struct twice2 : apply1<F, typename apply1<F, X>::type> {
};

template <class F, class X>
struct twice3: apply2<F, X>::type {

};

/**
 * lambda
 */
template <class X>
struct two_pointers: twice<typename lambda<std::add_pointer<_1>>::type, X> {
};

/**
 * apply in mpl
 */
template <class F, class X>
struct twice4: mpl::apply<F, typename mpl::apply<F, X>::type> {
};

int main()
{
    
    return 0;
}
