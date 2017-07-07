
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

#ifndef _SCALE_CALCULATOR_HPP_
#define _SCALE_CALCULATOR_HPP_

#include <vector> 
#include <chrono>
#include <optional> 
#include <memory>
#include <utility>
#include <string>
#include <algorithm>
#include <cmath>
#include <unordered_map>

#include "measurer.hpp"
#include "complexity_functions.hpp"

namespace balance
{
    using clock = std::chrono::steady_clock;
    using time_duration = std::chrono::duration< long,
                                                 std::nano >;

    class scale_calculator
    {
    private:
        std::vector<std::shared_ptr<std::optional<data_set>>> _datas;

        inline std::string compute_compl_impl(data_set const& first,
                                              data_set const& second) const;
        inline std::string find_best_fit(
            std::vector<std::string> const& candidates) const;
    public:
        inline scale_calculator(); 
	inline ~scale_calculator() =  default;

        inline measurer make_measurer();
        inline std::string compute_complexity();
    };


// implementation
    scale_calculator::
    scale_calculator()
    {
        _datas.reserve(5);
    }

    measurer
    scale_calculator::
    make_measurer()
    { 
        _datas.push_back(std::make_shared<std::optional<data_set>>());
        return measurer(_datas.back());
    }
    

    std::string
    scale_calculator::
    find_best_fit(std::vector<std::string> const& candidates) const
    {
        std::unordered_map<std::string, int> table;

        for(auto i : candidates) 
            ++table[i];
    
        auto best_fit = std::max_element(table.begin(),
                                         table.end(),
                                         [](auto first, auto second){
                                             return first.second < second.second;
                                         });
        return best_fit->first;
    }
 
    std::string 
    scale_calculator::
    compute_complexity() 
    {

        auto results = std::vector<std::string>();

        for(size_t i = 0; i < _datas.size(); ++i)
        {
            for(auto j = i + 1; j < _datas.size(); ++j)
            {
                auto result = compute_compl_impl(_datas[i]->value(),
                                                 _datas[j]->value());
                results.push_back(result);
            }
        }
    
        auto best = find_best_fit(results);
        return best;
    }

    std::string
    scale_calculator::
    compute_compl_impl(data_set const& first,
                       data_set const& second) const
    {
        data_set const* N1 = nullptr;
        data_set const* N2 = nullptr;

        if(first.first > second.first)
        {
            N2 = &first;
            N1 = &second;
        }
        else
        {
            N1 = &first; 
            N2 = &second;
        }
    
        double k = static_cast<double>(N2->first) / N1->first;
        int N = N1->first;

        double T = static_cast<double>(N2->second.count())
            / N1->second.count();

        std::vector<std::pair<double, std::string>> compared_result;

        for(auto i = 0u; i < complexity_functions.size(); ++i)
        {
            auto& f = complexity_functions[i].first;
            auto& str = complexity_functions[i].second;

            auto result = std::abs(T - f(k, N)); 

            compared_result.emplace_back(result, str);
        }
    
        auto it = std::min_element(compared_result.begin(),
                                   compared_result.end(),
                                   [](auto first, auto second){
                                       return first.first < second.first;
                                   });
        return it->second;
    }
}
#endif
