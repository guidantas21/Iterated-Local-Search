#include <iostream>
#include <vector>
#include <chrono>
#include <iomanip>

#include "ILS.hpp"
#include "solution.hpp"
#include "data.hpp"

int main(int argc, char** argv)
{
    ////////// LOAD DATA //////////

    auto data = Data(argc, argv[1]);

    std::cout << "-- Reading Data\n"; 
    data.read();

    const size_t SIZE = data.getDimension();

    int MAX_ITERATIONS = 50;
    int MAX_ITERATIONS_ILS = SIZE >= 150 ? SIZE/2 : SIZE;

    data.printMatrixDist();


    ////////// ILS EXECUTION //////////


    std::cout << "-- ILS\n"; 

    auto startTimer = std::chrono::high_resolution_clock::now();

    Solution solution = ILS(data.getMatrixCost(), SIZE, MAX_ITERATIONS, MAX_ITERATIONS_ILS);

    auto stopTimer = std::chrono::high_resolution_clock::now();

    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stopTimer - startTimer);


    ////////// RESULTS //////////


    std::cout << "\n-- Solution\n"; 

    std::cout << "\nBest tour of all:\n";
    printSolution(solution);

    std::cout << "Soluion cost: " << solution.cost << std::endl;


    float durationSeconds = (float) duration.count() / 1000000.0f;
    std::cout << "ILS execution duration: " << durationSeconds << " seconds\n";


    std::cout << "Status: ";

    // if (!isValid(solution, SIZE)) std::cout << "IN";

    std::cout << (!isValid(solution, SIZE) ? "IN" : "") << "VALID SOLUTION\n";

    return 0;
}

