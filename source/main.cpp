#include <iostream>
#include <vector>
#include <chrono>


#include "ILS.hpp"
#include "solution.hpp"
#include "data.hpp"

int main(int argc, char** argv)
{
    auto data = Data(argc, argv[1]);

    std::cout << "-- Reading Data\n"; 
    data.read();
    
    int MAX_ITERATIONS = 50;
    int MAX_ITERATIONS_ILS = 0;

    const size_t SIZE = data.getDimension();

    std::cout << "-- ILS\n"; 
    Solution solution = ILS(data.getMatrixCost(), SIZE, MAX_ITERATIONS, MAX_ITERATIONS_ILS);

    std::cout << "-- Solution\n"; 
    for (const int &v : solution.sequence)
    {
        std::cout << v << std::endl;
    }
    std::cout << endl;

    if (isValid(solution, SIZE))
    {
        std::cout << "VALID SOLUTION\n";
    }

    return 0;
}

