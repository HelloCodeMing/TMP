#include <type_traits>
#include <cassert>

#include <boost/mpl/vector_c.hpp>
#include <boost/mpl/int.hpp>
#include <boost/mpl/transform.hpp>
#include <boost/mpl/plus.hpp>
#include <boost/mpl/placeholders.hpp>

using namespace boost::mpl;
using namespace boost::mpl::placeholders;

int main()
{
    typedef vector_c<int, 1, 2, 3> t1;
    typedef typename transform<t1, plus<_1, int_<1>>>::type t3;
    return 0;
}
