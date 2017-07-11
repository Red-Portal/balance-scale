
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

namespace balance
{
    using initial_value_t = int;
    using size_ratio_t = double;
    using time_ratio_t = double;

    using refined_data_set = std::pair<size_ratio_t,
				       time_ratio_t>;

    class scale_simulator
    {
    private:
	std::vector<std::shared_ptr<std::optional<data_set>>> _data;
	
	refined_data_set compute_coeff(data_set& first, data_set& second);

	template<typename _Policy>
	void compute_simulated_graph(_Policy const& policy,
				     std::vector<refined_data_set> const& data);

    public:
	scale_simulator();
	~scale_simulator() = default;

	measurer make_measurer();

	template<typename _Policy>
	void graph_simulated_scale(_Policy const& policy);

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

    refined_data_set
    scale_simulator::
    compute_coeff(data_set& first, data_set& second)
    {
	data_set const* N1;
	data_set const* N2;

	if(first.first > second.first)
	{
	    N1 = &first;
	    N2 = &second;
	}
	else
	{
	    N1 = &second;
	    N2 = &first;
	}

	auto size_ratio = N2->first / N1->first;
	auto time_ratio = N2->second.count() / N1->second.count();

	return {size_ratio, time_ratio};
    }
    
    template<>
    void
    scale_simulator::
    compute_simulated_graph<policy::average>(
	policy::average const& policy,
	std::vector<refined_data_set> const& data)
    {
	auto size_ratio_total
	    = std::accumulate(
		data.begin(),
		data.end(),
		0,
		[](refined_data_set const& first,
		   refined_data_set const& second)
		{
		    return first.first + second.first;
		});

	auto time_ratio_total
	    = std::accumulate(
		data.begin(),
		data.end(),
		0,
		[](refined_data_set const& first,
		   refined_data_set const& second)
		{
		    return first.second + second.second;
		});

	auto size_ratio_avg = size_ratio_total / data.size();
	auto time_ratio_avg = time_ratio_total / data.size();


	auto step = size_ratio_avg / time_ratio_avg;

	std::vector<int> generated_sequence;

	auto policy_range = policy.get_graph_range();
	generated_sequence.reserve(
	    policy_range.second - policy_range.first);

	for(auto i = policy_range.first; i < policy_range.second; ++i)
    }

    template<typename _Policy>
    void
    scale_simulator::
    graph_simulated_scale(_Policy const& policy)
    {
	std::vector<refined_data_set> refined_data;

	data_set* initial;

	for(auto it = _data.begin(); it != _data.end(); ++it)
	{
	    if(auto& candidate = (*it)->value();
	       candidate.first < initial->first)
		initial = &candidate;

	    for(auto it2 = std::next(it); it2 != _data.end(); ++it2)
	    {
		refined_data.push_back(compute_coeff((*it)->value(),
						     (*it2)->value()));
	    }
	}
	compute_simulated_graph(policy_parameters, *initial, refined_data);
    }
}

#endif
