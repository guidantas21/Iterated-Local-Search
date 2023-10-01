#include "solution.hpp"

void printSolution(Solution& solution)
{   
    for (const auto& vertex : solution.sequence)
    {
        std::cout << vertex << " -> ";
    }

    std::cout << solution.sequence.front() << std::endl;
}

void calculateObjectiveValue(Solution& solution, double **adjacencyMatrix)
{
    solution.objectiveValue = 0;
    size_t solutionSize = solution.sequence.size();

    for (int i = 0; i < solutionSize - 1; i++)
    {
        solution.objectiveValue += adjacencyMatrix[solution.sequence[i]][solution.sequence[i+1]];
    }
}