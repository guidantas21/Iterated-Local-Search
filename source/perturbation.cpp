#include "perturbation.hpp"

double calculatePerturbationCost(Solution &solution, int posA, int sizeA, int posB, int sizeB, double **adjacencyMatrix);

Solution perturbation(Solution &solution, double **adjacencyMatrix)
{
    int smallestSegment = std::min(2, (int) std::ceil(solution.sequence.size() / 10.0f));

    int sizeA = getRandomNumber(smallestSegment, (std::ceil(solution.sequence.size() / 10.0f) + 2) - smallestSegment);
    int sizeB = getRandomNumber(smallestSegment, (std::ceil(solution.sequence.size() / 10.0f) + 2) - smallestSegment);

    int posA = getRandomNumber(1, (solution.sequence.size() - 1) - sizeA - sizeB);
    int posB = getRandomNumber(posA + sizeA, (solution.sequence.size() - 1) - sizeB);

    // std::cout << posA << ' ' << sizeA << std::endl;
    // std::cout << posB << ' ' << sizeB << std::endl;

    // std::cout << "s" <<solution.cost << std::endl;

    Solution newSolution = solution;

    double delta = calculatePerturbationCost(solution, posA, sizeA, posB, sizeB, adjacencyMatrix);

    newSolution.cost += delta;

    int small = std::min(sizeA, sizeB);

    for (int i = 0; i < small; i++)
    {
        std::swap(newSolution.sequence[posA + i], newSolution.sequence[posB + i]);
    }

    int difference = std::abs(sizeA - sizeB);

    std::vector<int> remainingSegment(difference);

    if (sizeA > sizeB)
    {
        for (int i = 0; i < difference; i++)
        {
            remainingSegment[i] = newSolution.sequence[posA + sizeB + i];
        }

        for (int i = posA + sizeA; i < posB + sizeB; i++)
        {
            newSolution.sequence[i - difference] = newSolution.sequence[i];
        }

        for (int i = 0; i < difference; i++)
        {
            newSolution.sequence[posB +sizeB - difference + i] = remainingSegment[i];
        }
    }

    else if (sizeA < sizeB)
    {
        for (int i = 0; i < difference; i++)
        {
            remainingSegment[i] = newSolution.sequence[posB + sizeA + i];
        }

        for (int i = posB + sizeA - 1; i >= posA + sizeA ; i--)
        {
            newSolution.sequence[i + difference] = newSolution.sequence[i];
        }

        for (int i = 0; i < difference; i++)
        {
            newSolution.sequence[posA + sizeA + i] = remainingSegment[i];
        }
    }

    // std::cout << "n" << newSolution.cost << std::endl;

    // calculateCost(&newSolution, adjacencyMatrix);

    // std::cout << "fdf" << newSolution.cost << std::endl;

    return newSolution;
}

double calculatePerturbationCost(Solution &solution, int posA, int sizeA, int posB, int sizeB, double **adjacencyMatrix)
{
    int vertex_posA = solution.sequence[posA];
    int vertex_posA_prev = solution.sequence[posA-1];
    int vertex_posA_last = solution.sequence[posA+sizeA-1];

    int vertex_posB = solution.sequence[posB];
    int vertex_posB_last = solution.sequence[posB+sizeB-1];
    int vertex_posB_last_next = solution.sequence[posB+sizeB];

    int currentCost, perturbationCost;

    if (posA + sizeA == posB)
    {
        currentCost = adjacencyMatrix[vertex_posA_prev][vertex_posA] 
            	    + adjacencyMatrix[vertex_posA_last][vertex_posB]
            	    + adjacencyMatrix[vertex_posB_last][vertex_posB_last_next];

        perturbationCost = adjacencyMatrix[vertex_posA_prev][vertex_posB]
                        + adjacencyMatrix[vertex_posB_last][vertex_posA]
                        + adjacencyMatrix[vertex_posA_last][vertex_posB_last_next];
    }
    else
    {
        int vertex_posA_last_next = solution.sequence[posA+sizeA];
        int vertex_posB_prev = solution.sequence[posB-1];
        

        currentCost = adjacencyMatrix[vertex_posA_prev][vertex_posA] // r
                    + adjacencyMatrix[vertex_posA_last][vertex_posA_last_next] // r
                    + adjacencyMatrix[vertex_posB_prev][vertex_posB] // r
                    + adjacencyMatrix[vertex_posB_last][vertex_posB_last_next]; // r

        perturbationCost = adjacencyMatrix[vertex_posB_prev][vertex_posA] // r
                        + adjacencyMatrix[vertex_posA_last][vertex_posB_last_next] // r
                        + adjacencyMatrix[vertex_posA_prev][vertex_posB] // r
                        + adjacencyMatrix[vertex_posB_last][vertex_posA_last_next]; // r
    }

    return perturbationCost - currentCost;
}