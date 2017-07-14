
// Copyright 2017 Red-Portal

// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at

// http://www.apache.org/licenses/LICENSE-2.0

// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

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
