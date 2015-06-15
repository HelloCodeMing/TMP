#include "common-header.hpp"
#include "splice.hpp"

using mpl::void_;
struct tree_tag;

template <class Node>
struct is_tree;

template <class Root = void_, class LHS = void_, class RHS = void_>
struct tree {
    typedef tree_tag tag;
    typedef tree type;
    typedef Root root;
    typedef LHS lhs;
    typedef RHS rhs;
//    typedef 
//    typename mpl::if_<
//                is_tree<LHS>,
//                LHS,
//                tree<LHS>
//            >::type lhs;
//    typedef 
//    typename mpl::if_<
//                is_tree<RHS>,
//                RHS,
//                tree<RHS>
//            >::type rhs;
};


template <class Node>
struct is_tree: false_ {};

template <class root, class lhs, class rhs>
struct is_tree<tree<root, lhs, rhs> > :true_ {};

template <class Node>
struct preorder_view
    :mpl::vector<Node> {
};

template <>
struct preorder_view<>
    :mpl::vector<> {
};

template <class Root, class lhs, class rhs>
struct preorder_view<tree<Root, lhs, rhs> >
    :splice<
        mpl::vector<Root>,
        typename preorder_view<lhs>::type,
        typename preorder_view<rhs>::type
    > {
};

template <class Node>
struct inorder_view
    :mpl::vector<Node> {
};

template <>
struct inorder_view<void_>
    :mpl::vector<> {
};

template <class root, class lhs, class rhs>
struct inorder_view<tree<root, lhs, rhs>>
    :splice<
        typename inorder_view<lhs>::type,
        mpl::vector<root>,
        typename inorder_view<rhs>::type
    > {
};

template <class Node>
struct postorder_view
    :mpl::vector<Node> {
};

template <>
struct postorder_view<void_> 
    :mpl::vector<> {
};
template <class root, class lhs, class rhs>
struct postorder_view<tree<root, lhs, rhs>>
    :splice<
        typename postorder_view<lhs>::type,
        typename postorder_view<rhs>::type,
        mpl::vector<root>
    >::type {
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
