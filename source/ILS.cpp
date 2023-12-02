#include "ILS.hpp"

Solution ILS(double **adjacencyMatrix, size_t size, int maxIterations, int maxIterationsILS)
{
    Solution bestOfAll;

    bestOfAll.cost = std::numeric_limits<double>::infinity();

    for (int i = 0; i < maxIterations; i++)
    {
        std::cout << "\n---- " << i << "\n\n";

        Solution currentSolution = construction(adjacencyMatrix, size);

        std::cout << "Current cost: " << currentSolution.cost << "\n";

        Solution bestOfIteraction = currentSolution;

        int iterationsILS = 0;

        while (iterationsILS <= maxIterationsILS)
        {
            localSearch(&currentSolution, adjacencyMatrix); // implementing

            if (currentSolution.cost < bestOfIteraction.cost)
            {
                bestOfIteraction = currentSolution;
                iterationsILS = 0;
            }

            // if (iterationsILS < 50)
            // {
            //     std::cout << "b" << currentSolution.cost << std::endl;
            //     // printSolution(currentSolution);
            // }

            currentSolution = perturbation(bestOfIteraction, adjacencyMatrix); // To implement    
            // if (iterationsILS < 50)
            // {
                // std::cout << currentSolution.cost << std::endl;
            //     // printSolution(currentSolution);
            // }
            iterationsILS++;

            // std::cout << "Best Iteration Cost: " << bestOfIteraction.cost << '\n';
        }

        if (bestOfIteraction.cost < bestOfAll.cost)
        {
            bestOfAll = bestOfIteraction;
        }

        std::cout << "Best Global Cost: " << bestOfAll.cost << '\n';
    }

    return bestOfAll;
}