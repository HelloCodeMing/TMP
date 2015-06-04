#include <boost/mpl/apply.hpp>

namespace mpl = boost::mpl;


template <class F, class Arg>
struct twice: mpl::apply<F, typename mpl::apply<F, Arg>::type> {};
