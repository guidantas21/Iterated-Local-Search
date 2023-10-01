#include <iostream>
#include <vector>

#include "solution.hpp"
#include "data.hpp"

int main(int argc, char** argv)
{
    auto data = Data(argc, argv[1]);

    data.read();
    

    size_t SIZE = data.getDimension();

    double **adjacencyMatrix = data.getMatrixCost();


    Solution solutionTest = {{1,2,3}, 0};

    calculateObjectiveValue(solutionTest, adjacencyMatrix);

    printSolution(solutionTest);


    for (size_t i = 0; i < dimension; ++i) 
    {
        delete[] adjacencyMatrix[i];
    }
    delete[] adjacencyMatrix;

    return 0;
}