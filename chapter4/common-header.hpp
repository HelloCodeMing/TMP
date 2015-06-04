#ifndef COMMON_HEADER_HPP
#define COMMON_HEADER_HPP

#include <type_traits>
#include <cassert>
#include <iterator>

#include <boost/mpl/apply.hpp>
#include <boost/mpl/plus.hpp>
#include <boost/mpl/int.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/mpl/vector_c.hpp>
#include <boost/mpl/transform.hpp>
#include <boost/mpl/lambda.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/mpl/equal_to.hpp>

namespace mpl = boost::mpl;
using namespace mpl::placeholders;

#endif
