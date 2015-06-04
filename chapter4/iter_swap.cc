#include "common-header.hpp"


struct fast_swap {
    template <class ForwardIterator1, class ForwardIterator2>
        static void do_it(ForwardIterator1 lhs, ForwardIterator2 rhs) {
            std::swap(*lhs, *rhs);
        }
};

struct reliable_swap {
    template <class ForwardIterator1, class ForwardIterator2>
        static void do_it(ForwardIterator1 lhs, ForwardIterator2 rhs) {
            typename std::iterator_traits<ForwardIterator1>::value_type
                tmp = *lhs;
            *lhs = *rhs;
            *rhs = tmp;
        }
};


template <class ForwardIterator1, class ForwardIterator2>
void iter_swap(ForwardIterator1 lhs, ForwardIterator2 rhs) {
    typedef std::iterator_traits<ForwardIterator1> traits1;
    typedef std::iterator_traits<ForwardIterator2> traits2;
    typedef typename traits1::value_type v1;
    typedef typename traits2::value_type v2;
    typedef typename traits1::reference r1;
    typedef typename traits2::reference r2;

    const bool use_swap = std::is_same<v1, v2>::value &&
                          std::is_reference<v1>::value;
    mpl::if_<mpl::bool_<use_swap>, fast_swap, reliable_swap>::type::do_it(lhs, rhs);
}


int main()
{
    int a = 1;
    int b = 2;
    iter_swap(a, b);
    printf("%d %d\n", a, b);
}
