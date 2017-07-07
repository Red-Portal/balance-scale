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
    auto  calculator = balance::scale_calculator();

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
