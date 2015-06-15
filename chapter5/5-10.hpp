#include "common-header.hpp"
#include "splice.hpp"

struct none;

template <class Node>
struct is_tree;

template <class Root = none, class LHS = none, class RHS = none>
struct tree {
    typedef Root root;
    typedef tree type;
    typedef 
    typename mpl::if_<
                is_tree<LHS>,
                LHS,
                tree<LHS>
            >::type lhs;
    typedef 
    typename mpl::if_<
                is_tree<RHS>,
                RHS,
                tree<RHS>
            >::type rhs;
};

template <class Node>
struct is_tree: false_ {};

template <class root, class lhs, class rhs>
struct is_tree<tree<root, lhs, rhs> > :true_ {};

template <class Node>
struct preorder_view 
    :splice<
        mpl::vector<typename Node::root>,
        typename preorder_view<typename Node::lhs>::type,
        typename preorder_view<typename Node::rhs>::type
    >::type {
};

template <class root>
struct preorder_view<tree<root, none, none> > 
    :mpl::vector<root> {
};

template <class Tree>
struct inorder_view
    :splice<
        typename inorder_view<typename Tree::lhs>::type,
        mpl::vector<typename Tree::root>,
        typename inorder_view<typename Tree::rhs>::type
     > {
};

template <class root>
struct inorder_view<tree<root, none, none> >
    :mpl::vector<root> {
};

template <class Tree>
struct postorder_view
    :splice<
        typename postorder_view<typename Tree::lhs>::type,
        typename postorder_view<typename Tree::rhs>::type,
        mpl::vector<typename Tree::root>
    > {
};

template <class root>
struct postorder_view<tree<root, none, none> > 
    :mpl::vector<root> {
};

namespace test_5_10 {

typedef tree<
            double,
            tree<void*, int, long>,
            char
        > tree_seq;

typedef tree<
            mpl::int_<1>,
            tree<mpl::int_<2>, mpl::int_<3>, mpl::int_<4> >,
            mpl::int_<5>
        > tree_seq1;

static_assert(
        mpl::equal<
            mpl::vector<short, int, long>,
            splice<
                mpl::vector<short>,
                mpl::vector<int>,
                mpl::vector<long>
            >::type
        >::value, 
        "splice");

static_assert(
        mpl::equal<
            preorder_view<tree_seq>::type,
            mpl::vector<double, void*, int, long, char>
        >::value,
        "preorder");

static_assert(
        mpl::equal<
            inorder_view<tree_seq>::type,
            mpl::vector<int, void*, long, double, char>
        >::value,
        "inorder");

static_assert(
        mpl::equal<
            postorder_view<tree_seq>::type,
            mpl::vector<int, long, void*, char, double>
        >::value,
        "postorder");

static_assert(
        mpl::equal<
            preorder_view<tree_seq1>::type,
            mpl::vector_c<int, 1, 2, 3, 4, 5>,
            mpl::equal_to<_, _>
        >::value,
        "tree_seq1 preorder");

static_assert(
        mpl::equal<
            inorder_view<tree_seq1>::type,
            mpl::vector_c<int, 3, 2, 4, 1, 5>,
            mpl::equal_to<_, _>
        >::value,
        "tree_seq1 inorder");

static_assert(
        mpl::equal<
            postorder_view<tree_seq1>::type,
            mpl::vector_c<int, 3, 4, 2, 5, 1>,
            mpl::equal_to<_, _>
        >::value,
        "tree_seq1 postorder");

} /* end of namespace test_5_10 */
