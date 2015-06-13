#include "tree.hpp"

struct inserter_impl {
    template <class Tree, class T>
    struct apply {
        typedef 
        typename
        mpl::eval_if<
            std::is_same<Tree, none>,
            tree<T>,
            typename mpl::if_<
                mpl::less<T, typename Tree::root>,
                tree<
                    typename Tree::root,
                    typename inserter_impl::template apply<
                        typename Tree::lhs,
                        T
                    >::type,
                    typename Tree::rhs
                >,
                tree<
                    typename Tree::root,
                    typename Tree::lhs,
                    typename inserter_impl::template apply<
                        typename Tree::rhs,
                        T
                    >::type
                >
            >::type
        >::type type; 
    };
};


template <class State>
struct binary_tree_inserter {
    typedef State state;
    typedef inserter_impl operation;
};

namespace test_6_3 {

typedef mpl::copy<
            mpl::vector_c<int, 17, 25, 10, 2, 11>,
            binary_tree_inserter<tree<> >
        >::type bst;

static_assert(
        mpl::equal<
            inorder_view<bst>,
            mpl::vector_c<int, 17, 25, 10, 2, 11>
        >::value,
        "binary_tree_inserter");
} /* end of namesapce test_6_3 */
