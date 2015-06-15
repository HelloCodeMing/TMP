#include "6-3.hpp"

/**
 * It is a leaf node.
 */
template <class Node, class Item>
struct binary_tree_search
    :mpl::equal_to<Node, Item> {
};

/**
 * It is branch node.
 */
template <class root, class lhs, class rhs, class Item>
struct binary_tree_search<tree<root, lhs, rhs>, Item>
    :mpl::eval_if<
        mpl::less<Item, root>,
        binary_tree_search<lhs, Item>,
        binary_tree_search<rhs, Item>
    > {
};


namespace test_6_4 {
    
typedef mpl::copy<
            mpl::vector_c<int, 17, 25, 10, 2, 11>,
            binary_tree_inserter<tree<> >
        >::type bst;

typedef binary_tree_search<bst, mpl::int_<11> >::type pos1;
typedef binary_tree_search<bst, mpl::int_<20> >::type pos2;
typedef mpl::end<bst>::type end_pos;

static_assert(
        pos1::value,
        "search 11");

static_assert(
        !pos2::value,
        "search 20");

} /* end of namespace test_6_4 */
