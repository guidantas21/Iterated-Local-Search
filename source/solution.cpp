#include "solution.hpp"

void printSolution(const Solution &solution)
{   
    for (const auto& vertex : solution.sequence)
    {
        std::cout << vertex << " -> ";
    }

    std::cout << solution.sequence.front() << '\n';
}

void calculateCost(Solution &solution, double **adjacencyMatrix)
{
    solution.cost = 0;
    size_t solutionSize = solution.sequence.size();

    for (size_t i = 0; i < solutionSize - 1; i++)
    {
        solution.cost += adjacencyMatrix[solution.sequence[i]][solution.sequence[i+1]];
    }
}