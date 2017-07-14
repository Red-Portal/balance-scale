
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

#ifndef _SCALE_SIMULATOR_HPP_
#define _SCALE_SIMULATOR_HPP_

#include <vector>
#include <utility>
#include <optional>
#include <memory>
#include <numeric>
#include <algorithm>

#include "measurer.hpp"
#include "policies.hpp"
#include "utility.hpp"

namespace balance
{
    using initial_value_t = int;
    using size_ratio_t = double;
    using time_ratio_t = double;

    using refined_data_set = std::tuple<initial_value_t,
                                        size_ratio_t,
                                        time_ratio_t>;

    class scale_simulator
    {
    private:
        std::vector<std::shared_ptr<std::optional<data_set>>> _data;
    
        template<typename _Policy>
        std::vector<double> compute_simulated_graph(
            int begin, int end,
            std::vector<refined_data_set> const& data) const;

        template<size_t N>
        std::vector<refined_data_set> compute_ratio(
            std::vector<data_set> data) const;
        
    public:
        scale_simulator();
        ~scale_simulator() = default;
        
        measurer make_measurer();

        template<typename _Policy>
        void graph_simulated_scale(int begin, int end);

    };

    scale_simulator::
    scale_simulator()
    {
        // preventing std::vector from reallocating
        _data.reserve(5);
    }

    measurer
    scale_simulator::
    make_measurer()
    {
        _data.push_back(std::make_shared<std::optional<data_set>>());
        return measurer(_data.back());
    }


    template<>
    std::vector<double>
    scale_simulator::
    compute_simulated_graph<policy::average>(
        int begin, int end,
        std::vector<refined_data_set> const& data) const
    {
        auto step_total = 
            std::accumulate(
                data.begin(),
                data.end(),
                0.0,
                [](refined_data_set const& first,
                   refined_data_set const& second)
                {
                    auto step_first =
                        std::get<2>(first) / std::get<1>(first); 
                    auto step_second = 
                        std::get<2>(second) / std::get<1>(second); 
                    return step_first + step_second;
                });

        auto averaged_step = 
            step_total / static_cast<double>(data.size());

        auto initial_value = std::get<0>(data.front());

        std::vector<double> result(end - begin);
        balance::generate_sequencing<double>(
            result.begin(),
            result.end(),
            initial_value,
            [averaged_step](auto it)
            {
                auto prev_it = std::prev(it);
                return *prev_it + averaged_step;
            });
        
        return {};
    }

    template<>
    std::vector<refined_data_set>
    scale_simulator::
    compute_ratio<2>(std::vector<data_set> data) const
    {
        data_set const* N2;
        data_set const* N1;

        if(data[0].first > data[1].first)
        {
            N2 = &data[0];
            N1 = &data[1];
        }
        else
        {
            N2 = &data[1];
            N1 = &data[0];
        }

        auto size_ratio = N2->first / N1->first;
        auto time_ratio = N2->second.count() / N1->second.count();

        return {{N1->first, size_ratio, time_ratio}};
    }

    template<size_t N>
    std::vector<refined_data_set>
    scale_simulator::
    compute_ratio(std::vector<data_set> data) const
    {
        static_assert(N <= 1, "Not enough data. Make more measurers");

        std::sort(data.begin(),
                  data.end(),
                  [](data_set const& first, data_set const& second){
                      return first.first < second.first; 
                  });

        std::vector<refined_data_set> result;

        balance::transform_between(
            data.begin(),
            data.end(),
            result.begin(),
            [](data_set const& first, data_set const& second)
            ->std::tuple<initial_value_t, size_ratio_t, time_ratio_t>
            {
                auto size_ratio =
                    second.first / first.first;
                auto time_ratio =
                    second.second.count() / first.second.count();

                return {first.first, size_ratio, time_ratio};
            });

        return result;
    }


    template<typename _Policy>
    void
    scale_simulator::
    graph_simulated_scale(int begin, int end)
    {
        std::vector<data_set> striped_data;

        std::transform(_data.begin(),
                       _data.end(),
                       striped_data.begin(),
                       [](auto element)
                       {
                           return element->value(); 
                       });

        std::vector<refined_data_set> processed_data;
        processed_data.reserve(20); 

        int const ELSE = 3;

        // optimization, assertion by size. size 1 should assert.
        if(striped_data.size() <= 1)
            processed_data = compute_ratio<1>(striped_data); 
        
        else if(striped_data.size() == 2)
            processed_data = compute_ratio<2>(striped_data);

        else
            processed_data = compute_ratio<ELSE>(striped_data);

        compute_simulated_graph<_Policy>(begin,
                                         end,
                                         processed_data);
    }
}

#endif
