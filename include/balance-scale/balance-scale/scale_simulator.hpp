
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
#include <chrono>
#include <utility>
#include <optional>
#include <memory>
#include <numeric>
#include <algorithm>

#include <iostream>

#include "measurer.hpp"
#include "policies.hpp"
#include "utility.hpp"

namespace balance
{
    using initial_value_t = data_set;
    using size_ratio_t = double;
    using time_ratio_t = double;

    using ratio_data_set = std::tuple<initial_value_t,
                                      size_ratio_t,
                                      time_ratio_t>;

    using plot_interval_t = std::pair<int, int>;

    class scale_simulator
    {
    private:
        std::vector<std::shared_ptr<std::optional<data_set>>> _data;
        std::pair<std::vector<int>,
                  std::vector<time_duration>> _simulated_range;
    
        template<typename _Policy>
        std::pair<std::vector<int>, std::vector<time_duration>>
        compute_simulated_range(plot_interval_t plot_interval,
                                std::vector<ratio_data_set>& data) const;

        template<size_t N>
        std::vector<ratio_data_set>
        compute_ratio(std::vector<data_set>& data) const;

    public:
        scale_simulator();
        ~scale_simulator() = default;
        
        measurer make_measurer();

        template<typename _Policy>
        void simulate_scale(int begin, int end);

        double get_simulated_time(int input_size);

        void
        plot() const;
        
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
    std::pair<std::vector<int>, std::vector<time_duration>>
    scale_simulator::
    compute_simulated_range<policy::average>(
        plot_interval_t plot_interval,
        std::vector<ratio_data_set>& data) const
    {
        auto const& smallest_input_data = std::get<0>(data.front());

        auto step_total = 
            std::accumulate(
                data.begin(),
                data.end(),
                0.0,
                [](time_ratio_t first,
                   ratio_data_set const& second)
                {
                    const int size_ratio = 1;
                    const int time_ratio = 2;

                    auto step_second = std::get<time_ratio>(second)
                    / std::get<size_ratio>(second); 
                    return first + step_second;
                });
        
        auto averaged_step = step_total / static_cast<int>(data.size());

        auto initial_value = smallest_input_data.second;
        auto initial_input_size = smallest_input_data.first;
        
        std::vector<time_duration> simulated_time(
            plot_interval.second - initial_input_size + 1);

        balance::generate_sequencing(
            simulated_time.begin(),
            simulated_time.end(),
            initial_value,
            [averaged_step](auto it)
            {
                auto prev_it = std::prev(it);
                return *prev_it * averaged_step;
            });

        int gen = plot_interval.first;
        std::vector<int> input_size(plot_interval.second -
                                    plot_interval.first + 1);
        std::generate(input_size.begin(),
                      input_size.end(),
                      [&gen](){ return gen++; });
        
        return {input_size, simulated_time};
    }

    template<>
    std::pair<std::vector<int>, std::vector<time_duration>>
    scale_simulator::
    compute_simulated_range<policy::adjacent>(
        plot_interval_t plot_interval,
        std::vector<ratio_data_set>& data) const
    {
        auto const& smallest_input_data = std::get<0>(data.front());
        auto initial_input_size = smallest_input_data.first;

        auto placeholder_duration =
            std::chrono::duration<double, std::nano>(0);

        // preventing dangling iterators
        data.reserve(data.size() + 1);

        auto data_end = data.end();

        // placeholder element in case sequence to be generated
        // is bigger than the sequence provided by the measured data
        if(plot_interval.second > std::get<0>(data.back()).first)
            data.emplace_back(
                std::make_tuple(std::make_pair(plot_interval.second,
                                               placeholder_duration), 0, 0));

        std::vector<time_duration> simulated_time(
            plot_interval.second - initial_input_size + 1);

        auto subsequence_begin = simulated_time.begin();
        for(auto it = data.begin(); it != data_end; ++it)
        {
            auto const sequence_data_set = 0; 
            auto const size_ratio = 1;
            auto const time_ratio = 2;

            // sry couldn't make this any simpler
            auto subsequence_range =
                std::get<sequence_data_set>(*std::next(it)).first
                - std::get<sequence_data_set>(*it).first;

            auto subsequence_end = subsequence_begin;
            std::advance(subsequence_end, subsequence_range + 1);

            auto subsequence_initial_value =
                std::get<sequence_data_set>(*it).second;
            auto step =
                std::get<time_ratio>(*it) / std::get<size_ratio>(*it);

            std::cout << "step: " << step << '\n'; 
            std::cout << "time ratio: " << std::get<time_ratio>(*it) << '\n'; 
            std::cout << "size ratio: " << std::get<size_ratio>(*it) << '\n'; 
            
            balance::generate_sequencing(
                subsequence_begin,
                subsequence_end,
                subsequence_initial_value,
                [step](auto it)
                {
                    auto prev_it = std::prev(it);
                    return *prev_it * step;
                });
        }

        int gen = plot_interval.first;
        std::vector<int> input_size(plot_interval.second -
                                    plot_interval.first + 1);
        std::generate(input_size.begin(),
                      input_size.end(),
                      [&gen](){ return gen++; });

        return {input_size, simulated_time};
    }

    template<>
    std::vector<ratio_data_set>
    scale_simulator::
    compute_ratio<2>(std::vector<data_set>& data) const
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

        auto size_ratio = static_cast<size_ratio_t>(N2->first) / N1->first;
        auto time_ratio = N2->second / N1->second;

        return {{*N1, size_ratio, time_ratio}};
    }

    template<size_t N>
    std::vector<ratio_data_set>
    scale_simulator::
    compute_ratio(std::vector<data_set>& data) const
    {
        std::sort(data.begin(),
                  data.end(),
                  [](data_set const& first, data_set const& second){
                      return first.first < second.first; 
                  });

        auto refined_size = static_cast<size_t>(
            std::ceil(static_cast<double>(data.size()) / 2));

        std::vector<ratio_data_set> result(refined_size);

        balance::transform_between(
            data.begin(),
            data.end(),
            result.begin(),
            [](data_set const& first, data_set const& second)
            ->std::tuple<initial_value_t, size_ratio_t, time_ratio_t>
            {
                auto size_ratio =
                    static_cast<size_ratio_t>(second.first) / first.first;
                auto time_ratio = second.second / first.second;

                return {first, size_ratio, time_ratio};
            });

        return result;
    }

    void
    scale_simulator::
    plot() const
    {
        // plt::plot(plot_data.first, plot_data.second);
        // plt::xlim(plot_data.first.front(), plot_data.first.back());
        // plt::show();

        for(auto i = 0u; i < _simulated_range.first.size(); ++i)
        {
            std::cout << _simulated_range.first[i]
                      << "  "
                      << _simulated_range.second[i].count()
                      << '\n';
        }
    }


    template<typename _Policy>
    void
    scale_simulator::
    simulate_scale(int begin, int end)
    {
        std::vector<data_set> striped_data(_data.size());

        std::transform(_data.begin(),
                       _data.end(),
                       striped_data.begin(),
                       [](auto const& element)
                       {
                           return element->value(); 
                       });

        std::vector<ratio_data_set> ratio_data_sets;

        int const ELSE = 3;

        // optimization, assertion by size. size 1 should assert.
        if(striped_data.size() == 2)
            ratio_data_sets = compute_ratio<2>(striped_data);
        else
            ratio_data_sets = compute_ratio<ELSE>(striped_data);

        auto range = std::make_pair(begin, end);
        auto plot_data =
            compute_simulated_range<_Policy>(range,
                                             ratio_data_sets);
        
        _simulated_range = std::move(plot_data);
    }

    double
    scale_simulator::
    get_simulated_time(int input_size) 
    {
        for(auto i = 0u; i < _simulated_range.first.size(); ++i)
        {
            if(_simulated_range.first[i] == input_size)
                return _simulated_range.second[i].count();
        }

        return 0;
    }
}

#endif
