#include <iostream>
#include <vector>

#include "ILS.hpp"
#include "solution.hpp"
#include "data.hpp"

int main(int argc, char** argv)
{
    auto data = Data(argc, argv[1]);

    data.read();
    
    int MAX_ITERATIONS = 1;
    int MAX_ITERATIONS_ILS = 0;

    const size_t SIZE = data.getDimension();

    double **adjacencyMatrix = data.getMatrixCost();

    ILS(adjacencyMatrix, SIZE, MAX_ITERATIONS, MAX_ITERATIONS_ILS);

    return 0;
}