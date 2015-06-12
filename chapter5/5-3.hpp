#include "common-header.hpp"
#include "slice.hpp"
#include "tiny.hpp"

template <class Tiny, int Pos, class T>
struct tiny_insert;

template <class Tiny, class T>
struct tiny_insert<Tiny, 0, T> 
    :tiny<T, typename Tiny::t0, typename Tiny::t1> {
};

template <class Tiny, class T>
struct tiny_insert<Tiny, 1, T>
    :tiny<typename Tiny::t0, T, typename Tiny::t1> {
};

template <class Tiny, class T>
struct tiny_insert<Tiny, 2, T>
    :tiny<typename Tiny::t0, typename Tiny::t1,T> {
};

namespace boost { namespace mpl {

template <>
struct insert_impl<tiny_tag> {
    template <class Tiny, class Pos, class X>
    struct apply
        :tiny_insert<
            Tiny, 
            mpl::distance<typename mpl::begin<Tiny>::type, Pos>::value,
            X> {
    };
};


}}/* end of namespace boost::mpl */

/**
 * Test.
 */
namespace test_5_3{

typedef tiny<short, int> t1;
typedef mpl::insert<t1, mpl::begin<t1>::type, long>::type t2;
static_assert(
        std::is_same<
            mpl::front<t2>::type,
            long
        >::value,
        "insert");
}/* end of test_5_3 namespace */
