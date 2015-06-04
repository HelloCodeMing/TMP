#include <type_traits>
#include <cassert>

#include <boost/mpl/vector_c.hpp>
#include <boost/mpl/int.hpp>
#include <boost/mpl/plus.hpp>
#include <boost/mpl/multiplies.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/mpl/transform.hpp>

namespace mpl = boost::mpl;
using namespace boost::mpl::placeholders;

int main()
{
    typedef mpl::vector_c<int, 1, 2, 3> t1;
    typedef mpl::vector_c<int, 1, 4, 9> t3;
    typedef typename mpl::transform<t1, mpl::multiplies<_1, _1>>::type t2;
    // static_assert((std::is_same<t2::type, t3::type>::value), "same or not?");
    return 0;
}
