#ifndef _COMPLEXITY_FUNCTIONS_
#define _COMPLEXITY_FUNCTIONS_

#include <vector>
#include <functional>
#include <string>
#include <cmath>

namespace balance
{
    enum class complexity{constant = 0,
                          linear = 1,
                          square = 2,
                          logn = 3,
                          nlogn = 4};

    std::vector<std::pair
		<std::function<double(double, int)>,
		 std::string>>  complexity_functions = { 
	    {
		    [](double k, int N) -> double
		    {
			    return 1; 
		    }, "constant"
	    },

	    {
		    [](double k, int N) -> double
		    {
			    return k; 
		    }, "linear"
	    },

	    {
		    [](double k, int N) -> double
		    {
			    return k * k; 
		    }, "square"
	    },

	    {
		    [](double k, int N) -> double
		    {
			    double N_f = static_cast<double>(N);
			    return 1 + std::log10(k) / std::log10(N_f); 
		    }, "logn"
	    },

	    {
		    [](double k, int N) -> double
		    {
			    double N_f = static_cast<double>(N);
			    return k * (1 + std::log10(k) / std::log10(N_f)); 
		    }, "nlogn"
	    }
    };
}

#endif
