#include <balance-scale/balance-scale.hpp>
#include <time.h>
#include <iostream>

int mult(int x, int y)
{
    int result = 0;
    for(int i = 0; i < x; ++i)
        result += y;
    return result;
}

int main()
{
    auto calc = balance::scale_calculator();

    auto measur1 = calc.make_measurer();
    auto measur2 = calc.make_measurer();

    {
        measur1.start(1000);


        std::cout << "multiplying 1000 by 1000: " 
                  << mult(1000, 1000) << std::endl;

        measur1.end();
    }

    {
        measur1.start(100000);

        std::cout << "multiplying 1000 by 100000: " 
                  << mult(100000, 1000) << std::endl;

        measur1.end();
    }

    auto result = calc.compute_complexity();

    std::cout << "result: " << result << std::endl;

    return 0;
}
