#include "common-header.hpp"

template <class T>
struct is_data_member_pointer 
    : mpl::if_<
        mpl::and_<
            std::is_member_pointer<T>,
            std::is_object<
                typename std::remove_pointer<T>::type
                >
            >,
        mpl::true_,
        mpl::false_
        >
        
        {
};

struct Dog {
    int age;
};

static_assert(std::is_same<
                mpl::true_,
                is_data_member_pointer<int Dog::*>::type
                >::value, "is data_member_pointer");

template <class Fn>
struct is_pointer_to_function
    : mpl::and_<
        std::is_pointer<Fn>,
        std::is_function<
          typename std::remove_pointer<Fn>::type
            > 
      > {
      };

static_assert(std::is_same<
                is_pointer_to_function<char* (*)(int)>::type,
                mpl::true_>::value, "is_pointer_to_function");

static_assert(std::is_same<
                is_pointer_to_function<char>::type,
                mpl::false_>::value, "not a pointer_to_function");

template <class Fn>
struct is_reference_to_function
    : mpl::and_<
        std::is_reference<Fn>,
        std::is_function<
            typename std::remove_reference<Fn>::type
            >
      > {
      };


template <class T>
struct is_reference_to_non_const 
    : mpl::and_<
        std::is_reference<T>,
        mpl::not_<
            std::is_const<
                typename std::remove_reference<T>::type
                         >
                 >
               > {
};

static_assert(is_reference_to_function<std::add_lvalue_reference<char(char)>::type>::value, "reference to function");

static_assert(is_reference_to_non_const<int&>::value, "reference to non const");
