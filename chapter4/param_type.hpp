#include "common-header.hpp"

/**
 * Choose T if T is a scalar, else choose const T&.
 */
template <class T>
struct param_type : mpl::if_<typename std::is_scalar<T>::type, 
                             T,
                             typename std::add_lvalue_reference<const T>::type> {
    // use add_lvalue_reference instead of const T&, to avoid the situation that T is a reference.
};

template <class T>
struct param_type2 : mpl::eval_if <
                        std::is_scalar<T>,
                        mpl::identity<T>,
                        std::add_lvalue_reference<const T>> {
                        };

/**
 * if metafunction
 */

static_assert(std::is_same<int, param_type<int>::type >::value, "int");
static_assert(std::is_same<const std::string&, param_type<std::string>::type >::value, "int&");

static_assert(std::is_same<int, my_if< 1 < 2, int, void>::type>::value, "my_if");
