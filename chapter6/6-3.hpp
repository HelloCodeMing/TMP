#include "tree.hpp"

namespace boost { namespace mpl {

template <>
struct push_back_impl<tree_tag> {
    template <class Item, class Node>
    struct apply
        :mpl::eval_if<
            mpl::less<Item, Node>,
            tree<Item, Node>,
            tree<Item, void_, Node>
         > {
    };

    template <class Root, class LHS, class RHS, class Node>
    struct apply<tree<Root, LHS, RHS>, Node> 
        :mpl::eval_if<
            mpl::less<Node, Root>,
            tree<
                Root,
                typename apply<LHS, Node>::type,
                RHS
            >,
            tree<
                Root,
                LHS,
                typename apply<RHS, Node>::type
            >
        > {
    };

    template <class Node>
    struct apply<tree<>, Node> 
        :tree<Node> {
    };

    template <class Node>
    struct apply<void_, Node> 
        : tree<Node> {
    };
};

}} /* end of namespace boost::mpl */

template <class State>
struct binary_tree_inserter {
    typedef State state;
    typedef mpl::push_back<_, _> operation;
};

namespace test_6_3 {

typedef mpl::copy<
            mpl::vector_c<int, 3, 4>,
            binary_tree_inserter<tree<> >
        >::type bst;

static_assert(
        mpl::equal<
            inorder_view<bst>::type,
            mpl::vector_c<int, 3, 4>,
            mpl::equal_to<_, _>
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
