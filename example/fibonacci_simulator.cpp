
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
#include <iostream>
#include <chrono>

int64_t fib(int64_t num)
{
    if(num == 0 || num == 1)
        return 1;
    else
        return fib(num - 1) + fib(num - 2);
}

int main()
{
    auto calc = balance::scale_simulator();

    auto measur1 = calc.make_measurer();
    auto measur2 = calc.make_measurer();
    auto measur3 = calc.make_measurer();


    {
        int const num = 13;

        measur3.start(num);
        int result = fib(num);
        measur3.end();

        std::cout << num << "th fibonacci number is " 
                  << result << std::endl;
    } 

    {
        int const num = 1;

        measur1.start(num);
        int result = fib(num);
        measur1.end();

        std::cout << num << "th fibonacci number is " 
                  << result << std::endl;
    } 

    {
        int const num = 10;

        measur2.start(num);
        int result = fib(num);
        measur2.end();

        std::cout << num << "th fibonacci number is " 
                  << result << std::endl;
    } 
    
    auto start = std::chrono::steady_clock::now();
    calc.simulate_scale<balance::policy::average>(10, 20); 
    auto end = std::chrono::steady_clock::now();

    const int size = 15;

    std::cout << "simulated time for " << size << " input size: ";
    std::cout << calc.get_simulated_time(size) << std::endl;
    auto duration = end - start;

    std::cout << "benchmark: "
              << std::chrono::duration_cast<std::chrono::microseconds>(duration).count()
              << std::endl;

    return 0;
}
