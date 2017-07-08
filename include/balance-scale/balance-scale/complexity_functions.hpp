
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

#ifndef _COMPLEXITY_FUNCTIONS_
#define _COMPLEXITY_FUNCTIONS_

#include <vector>
#include <functional>
#include <string>
#include <cmath>

namespace balance::approx
{
    enum class complexity{constant = 0,
                          linear = 1,
                          square = 2,
                          logn = 3,
                          nlogn = 4};

    std::vector<std::string> compl_strings = {
	"constant",
	"linear",
	"square",
	"logn",
	"nlogn"
    };


    std::vector<std::pair
                <std::function<double(double, int)>,
		 complexity>>  compl_functions = { 
        {
            [](double k, int N) -> double
            {
                (void)N;
                (void)k;
                return 1; 
            }, complexity::constant
        },

        {
            [](double k, int N) -> double
            {
                (void)N;
                return k; 
            }, complexity::linear
        },

        {
            [](double k, int N) -> double
            {
                (void)N;
                return k * k; 
            }, complexity::square
        },

        {
            [](double k, int N) -> double
            {
                double N_f = static_cast<double>(N);
                return 1 + std::log10(k) / std::log10(N_f); 
            }, complexity::logn
        },

        {
            [](double k, int N) -> double
            {
                double N_f = static_cast<double>(N);
                return k * (1 + std::log10(k) / std::log10(N_f)); 
            }, complexity::nlogn
        }
    };
}

#endif
