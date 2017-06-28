#ifndef _COMPLEXITY_FUNCTIONS_
#define _COMPLEXITY_FUNCTIONS_

#include <vector>
#include <functional>
#include <cmath>

namespace balance
{
    constexpr std::vector<std::function<double(int, int)>> complexity_functions
    constexpr void compl_funcs_init()
    {
        complexity_functions.push_back(
            [](int k, int N) -> double
            {
                return 1; 
            });

        complexity_functions.push_back(
            [](int k, int N) -> double
            {
                return k; 
            });

        complexity_functions.push_back(
            [](int k, int N) -> double
            {
                return k * k; 
            });

        complexity_functions.push_back(
            [](int k, int N) -> double
            {
                double k_f = static_cast<double>(k);
                double N_f = static_cast<double>(N);
                return 1 + std::log10(k) / std::log10(N); 
                
            });

        complexity_functions.push_back(
            [](int k, int N) -> double
            {
                double k_f = static_cast<double>(k);
                double N_f = static_cast<double>(N);
                return k * (1 + std::log10(k) / std::log10(N)); 
                
            });
    }

}

#endif
