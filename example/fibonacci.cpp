
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

#include <balance-scale/balance-scale.hpp>
#include <time.h>
#include <iostream>

int64_t fib(int64_t num)
{
    if(num == 0 || num == 1)
        return 1;
    else
        return fib(num - 1) + fib(num - 2);
}

int main()
{
    auto calc = balance::scale_calculator();

    auto measur1 = calc.make_measurer();
    auto measur2 = calc.make_measurer();
    auto measur3 = calc.make_measurer();


    {
        int const num = 13;
        measur3.start(num);

        std::cout << num << "th fibonacci number is " 
                  << fib(num) << std::endl;

        measur3.end();
    } 

    {
        int const num = 10;
        measur2.start(num);

        std::cout << num << "th fibonacci number is " 
                  << fib(num) << std::endl;

        measur2.end();
    } 

    {
        int const num = 1;
        measur1.start(num);

        std::cout << num << "th fibonacci number is "
                  << fib(num) << std::endl;

        measur1.end();
    }

    auto result = calc.compute_complexity();

    std::cout << "approximate complexity: " << result << std::endl;

    return 0;
}
