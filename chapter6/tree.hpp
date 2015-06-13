#include "common-header.hpp"

struct none;

template <class Root = none, class LHS = none, class RHS = none>
struct tree {
    typedef tree type;
    typedef Root root;
    typedef 
    typename mpl::if_<
                std::is_scalar<LHS>,
                tree<LHS>,
                LHS
            >::type lhs;
    typedef 
    typename mpl::if_<
                std::is_scalar<RHS>,
                tree<RHS>,
                RHS
            >::type rhs;
};

struct none: tree<> {};

template <class ...Arg> 
struct splice {};

template <class Seq>
struct splice<Seq>: Seq {};

template <class Head, class ...Tail>
struct splice<Head, Tail...>
    :mpl::copy<
        typename splice<Tail...>::type,
        mpl::back_inserter<Head>
    > {
};


template <class Tree>
struct preorder_view 
    :splice<
        mpl::vector<typename Tree::root>,
        typename preorder_view<typename Tree::lhs>::type,
        typename preorder_view<typename Tree::rhs>::type
    > {
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

typedef tree<
            mpl::int_<0>,
            tree<mpl::int_<1>, mpl::int_<2>, mpl::int_<3> >,
            mpl::int_<4>
        > tree_seq1;
static_assert(
        mpl::equal<
            inorder_view<tree_seq1>::type,
            mpl::vector_c<int, 1, 3, 0, 4>
        >::value,
        "inorder2");
} /* end of namespace test_5_10 */
