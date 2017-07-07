# Balance-Scale
## Introduction
Balance-Scale is an algorithm scalibility approximating header-only library.
Based on [Ben Deane's talk at CppCon 2015](https://youtu.be/OPoZWnYIcP4).

## How to use

include the 'include' directory.

``` c++
#include <balance-scale/balance-scale.hpp>
    
auto calculator = balance::scale-calculator();
    
auto measurer1 = calculator.make_measurer();
auto measurer2 = calculator.make_measurer();
    
measurer1.start(N) // N  is the size of the algorithm input
    
/*
	algorithm implementation
*/
    
measurer1.end()

measurer2.start(N_2) // N_2  is the size of a different algorithm input
    
/*
	algorithm implementation
*/
    
measurer2.end()
    
auto result = calculator.compute_complexity();
```

Make a measurer and measure the blocks of your algorithms with varying input sizes.
In order to compute the scalability, you should measure with at least two measurer objects.
The calculator object retrieves all the measurers' datas automatically and returns the closest complexity.

## TODO
active development under process. This library is subject to very frequent update and change of interface.
