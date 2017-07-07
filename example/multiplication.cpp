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

    auto measurer1 = calculator.make_measurer();
    auto measurer2 = calculator.make_measurer();

    const int Y = 1000;

    {
        int X = 100;
        measurer1.start(X); 

        std::cout << "multiplying " << X << " with " << Y << " is "
                  << multiplication(X, Y) << std::endl;
        measurer1.end();
    }

    {
        int X = 100000;
        measurer2.start(X); 

        std::cout << "multiplying " << X << " with " << Y << " is "
                  << multiplication(X, Y) << std::endl;
        measurer2.end();
    }

    auto complexity = calculator.compute_complexity();

    std::cout << "approximate complexity is "<< complexity << std::endl;

    return 0; 
}
