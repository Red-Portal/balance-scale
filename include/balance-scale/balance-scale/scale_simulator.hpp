
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

#include "measurer.hpp"

namespace balance
{
    class scale_simulator
    {
    private:
	std::vector<std::shared_ptr<std::optional<data_set>>> _data;

    public:
	scale_simulator();
	measurer make_measurer();
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
}

#endif
