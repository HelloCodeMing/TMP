#ifndef EVAL_HPP
#define EVAL_HPP
#include "common-header.hpp"

template <class T>
struct param_type: mpl::eval_if< 
                   std::is_scalar<T>,
                   mpl::identity<T>,
                   std::add_lvalue_reference<const T>> {
                   };

/* main */
static_assert(std::is_same<int, param_type<int>::type>::value, "int");
static_assert(std::is_same<const std::string&, param_type<std::string>::type>::value, "string");

#endif
