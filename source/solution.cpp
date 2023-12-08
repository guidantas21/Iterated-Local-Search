#include "solution.hpp"

void printSolution(const Solution &solution)
{   
    size_t range = solution.sequence.size() - 1;

    for (size_t i = 0; i < range; ++i)
    {
        if (i > 0 && i % 20 == 0)
        {
            std::cout << std::endl;
        }
        std::cout << solution.sequence[i] << " -> ";
    }
    std::cout << solution.sequence.front() << std::endl;
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

bool isValid(const Solution &solution, const size_t &size, double **adjacencyMatrix)
{
    if (solution.sequence.size() == size+1 && solution.cost > 0 && solution.sequence[0] == 0)
    {
        std::unordered_set<int> solutionSet(solution.sequence.begin(), solution.sequence.end());

        // check duplicated vertices
        if (solutionSet.size() == size)
        {
            for (size_t i = 1; i < solution.sequence.size(); ++i)
            {
                if (solution.sequence[i] < 0)
                {
                    return false;
                }
            }

            Solution aux = solution;

            calculateCost(aux, adjacencyMatrix);

            if (solution.cost == aux.cost)
            {
                return true;   
            }
        }
    }
    return false;
}