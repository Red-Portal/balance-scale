#ifndef _SCALE_CALCULATOR_HPP_
#define _SCALE_CALCULATOR_HPP_

#include <vector> 
#include <chrono>
#include <optional> 
#include <utility>
#include <string>
#include <algorithm>

#include "measurer.hpp"

namespace balance
{
    using clock = std::chrono::high_resolution_clock;
    using time_point = std::chrono::time_point< clock,
                                                std::nano >;
    using data_set = std::pair<int, time_point>;

    enum class complexity{constant, linear};

    class scale_calculator
    {
    private:
        std::vector<std::optional<data_set>> _datas;

        inline complexity compute_compl_impl(data_set const& first,
                                             data_set const& second);
    public:
        inline scale_calculator();
        inline ~scale_calculator() =  default;

        inline measurer make_measurer();
        inline complexity compute_complexity();
    };


    // implementation

    scale_calculator::
    scale_calculator
    {
        compl_funcs_init(); 
    }

    measurer
    scale_calculator::
    make_measurer()
    {
        _datas.push_back({});
        return measurer(_datas.back());
    }

    complexity
    scale_calculator::
    compute_compexity()
    {
        auto results = vector<complexity>();

        for(auto i = 0; i < _datas; ++i)
        {
            for(auto j = i; j < _datas; ++j)
            {
                auto result = compute_compl_impl(_datas[i],
                                                 _datas[j]);
                results.push_back(result);
            }
        }
    }

    complexity
    scale_calculator::
    compute_compl_impl(data_set const& first,
                       data_set const& second)
    {
        
    }
}

#endif
