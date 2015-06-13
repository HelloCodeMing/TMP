#include "tree.hpp"

template <class Tree, class T>
struct inserter_impl 
    :mpl::if_<
        mpl::less<T, typename Tree::root>,
        tree<
            typename Tree::root,
            typename inserter_impl<typename Tree::lhs, T>::type,
            typename Tree::rhs
        >,
        tree<
            typename Tree::root,
            typename Tree::lhs,
            typename inserter_impl<typename Tree::rhs, T>::type
        >
    > {
};

template <class T>
struct inserter_impl<none, T> 
    :tree<T> {
};

template <class T>
struct inserter_impl<tree<none, none, none>, T> 
    :tree<T> {
};

struct inserter {
    template <class Tree, class T>
    struct apply 
        :inserter_impl<Tree, T> {
    };
};


template <class State>
struct binary_tree_inserter {
    typedef State state;
    typedef inserter operation;
};

namespace test_6_3 {

typedef mpl::copy<
            mpl::vector_c<int, 3, 4>,
            binary_tree_inserter<tree<> >
        >::type bst;
static_assert(
        mpl::equal<
            inorder_view<bst>::type,
            mpl::vector_c<int, 3, 4>
        >::value, 
        "4, 3");

typedef mpl::copy<
            mpl::vector_c<int, 17, 25, 10, 2, 11>,
            binary_tree_inserter<tree<> >
        >::type bst1;

//static_assert(
//        mpl::equal<
//            inorder_view<bst>::type,
//            mpl::vector_c<int, 2, 10, 11, 17, 25>
//        >::value,
//        "binary_tree_inserter");
} /* end of namesapce test_6_3 */
