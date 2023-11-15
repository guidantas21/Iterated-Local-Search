#include <iostream>
#include <vector>
#include <chrono>
#include <iomanip>

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

    data.printMatrixDist();

    std::cout << "-- ILS\n"; 

    auto startTimer = std::chrono::high_resolution_clock::now();

    Solution solution = ILS(data.getMatrixCost(), SIZE, MAX_ITERATIONS, MAX_ITERATIONS_ILS);

    auto stopTimer = std::chrono::high_resolution_clock::now();

    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stopTimer - startTimer);

    

    std::cout << "-- Solution\n"; 

    std::cout << "Best tour of all:\n";
    for (const int &v : solution.sequence)
    {
        std::cout << v << std::endl;
    }
    std::cout << endl;

    calculateCost(solution, data.getMatrixCost());

    std::cout << "Soluion cost: " << solution.cost << std::endl;

    float durationSeconds = (float) duration.count() / 1000000.0f;

    std::cout << "ILS execution duration: " << durationSeconds << " seconds\n";

    std::cout << "Status: ";

    if (!isValid(solution, SIZE))
    {
        std::cout << "IN";
    }

    std::cout << "VALID SOLUTION\n";

    return 0;
}

