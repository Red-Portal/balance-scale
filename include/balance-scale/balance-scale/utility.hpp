#ifndef _UTILITY_HPP_
#define _UTILITY_HPP_

#include <iterator>

// template<int N, int P>
// struct Pow
// {
//     enum {value = N * Pow<N, P-1>::value};
// };

// template<int N>
// struct Pow<N, 0>
// {
//     enum {value = N}; 
// };

namespace balance
{
    template<typename _IIter, typename _Funct>
    constexpr void
    for_between(_IIter iBegin, _IIter iEnd, _Funct func)
    {
        auto end = std::prev(iEnd);
        for(_IIter it = iBegin; it != end; ++it) 
        {
            func(*it, *std::next(it));
        }
    }

    template<typename _IIter, typename _OIter, typename _BinaryOp>
    constexpr void
    transform_between(_IIter iBegin, _IIter iEnd,
                      _OIter OBegin, _BinaryOp binary_op)
    {
        auto end = std::prev(iEnd);

        for(_IIter it = iBegin; it != end; ++it, ++OBegin) 
            *OBegin = binary_op(*it, *std::next(it));

        return OBegin;
    }
}
#endif
