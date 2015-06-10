#include "common-header.hpp"

//template <class First, class Last>
//struct concat {
//    
//};
//
//template <class T>
//struct double_first_half {
//    
//};
//
//static_assert(
//        mpl::equal<
//            double_first_half< mpl::vector_c<int, 1, 2, 3, 4> >::type,
//            mpl::vector_c<int, 2, 4, 3, 4>
//        >::type::value,
//        "equal");

/**
 * fold test
 */
template <class first, class last, class init, class bo> 
struct fold 
    :mpl::if_<
        std::is_same<first, last>,
        init,
        fold<
            typename mpl::next<first>::type,
            last,
            typename mpl::apply<
                bo,
                init,
                typename mpl::deref<first>::type
            >::type,
            bo
        >
     >
{ };

typedef mpl::vector_c<int, 1> vec0;
typedef mpl::int_<1> answer0;
typedef fold<
            mpl::begin<vec0>::type,
            mpl::end<vec0>::type,
            mpl::int_<0>,
            mpl::plus<_1, _2>
        >::type fold_res0;

static_assert(std::is_same<answer0, fold_res0>::value, "fold one element");

typedef mpl::vector_c<int, 1, 2, 3, 4> vec_c;
typedef mpl::int_<10> answer;
typedef fold<
            mpl::begin<vec_c>::type,
            mpl::end<vec_c>::type,
            mpl::int_<0>,
            mpl::plus<_1, _2>
        >::type fold_res;

static_assert( std::is_same<answer, fold_res>::value, "fold more elements");
    

/* 
 * push_back test
 */
typedef mpl::vector<short, unsigned, short> vec;
typedef mpl::vector<short, unsigned, short, long> vec1;

static_assert(
        mpl::equal<
            vec1,
            mpl::push_back<vec, long >::type
        >::type::value,
        "push_back");
