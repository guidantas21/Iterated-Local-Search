#include "ILS.hpp"

Solution ILS(double **adjacencyMatrix, size_t size, int maxIterations, int maxIterationsILS)
{
    Solution bestOfAll;

    bestOfAll.cost = std::numeric_limits<double>::infinity();


    for (int i = 0; i < maxIterations; i++)
    {
        Solution currentSolution = construction(adjacencyMatrix, size); // To implement

        Solution bestOfIteraction = currentSolution;


        int iterationsILS = 0;

        while (iterationsILS <= maxIterationsILS)
        {
            localSearch(); // To implement

            if (currentSolution.cost < bestOfIteraction.cost)
            {
                bestOfIteraction = currentSolution;
                iterationsILS = 0;
            }

            currentSolution = pertubation(); // To implement
            iterationsILS++;
        }

        if (bestOfIteraction.cost < bestOfAll.cost)
        {
            bestOfAll = bestOfIteraction;
        }
    }

    return bestOfAll;
}