
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

#include <iostream>

#include <balance-scale/balance-scale.hpp>


int64_t multiplication(int64_t X, int64_t Y)
{
    int64_t result = 0;

    for(int64_t i = 0; i < X; ++i)
        result += Y;

    return result;
}

int main()
{
    auto  calculator = balance::scale_approximator();

    const int Y = 1000;

    {
        int X = 100;

        auto measurer = calculator.make_measurer();
        measurer.start(X); 

        std::cout << "multiplying " << X << " with " << Y << " is "
                  << multiplication(X, Y) << std::endl;
    }

    {
        int X = 100000;

        auto measurer = calculator.make_measurer();
        measurer.start(X); 

        std::cout << "multiplying " << X << " with " << Y << " is "
                  << multiplication(X, Y) << std::endl;
    }

    {
        int X = 10;

        auto measurer = calculator.make_measurer();
        measurer.start(X); 

        std::cout << "multiplying " << X << " with " << Y << " is "
                  << multiplication(X, Y) << std::endl;
    }

    {
        int X = 500;

        auto measurer = calculator.make_measurer();
        measurer.start(X); 

        std::cout << "multiplying " << X << " with " << Y << " is "
                  << multiplication(X, Y) << std::endl;
    }

    auto complexity = calculator.compute_complexity();

    std::cout << "approximate complexity is "<< complexity << std::endl;

    return 0; 
}
