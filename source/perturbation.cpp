#include "perturbation.hpp"

double calculatePerturbationCost(std::vector<int> &sequence, int posA, int sizeA, int posB, int sizeB, double **adjacencyMatrix);

int randomNumber(int minLimit, int maxLimit);

Solution perturbation(Solution *solution, double **adjacencyMatrix)
{
    int sequenceSize = solution->sequence.size();

    int maxLimit = std::ceil(sequenceSize / 10.0f);
    int minLimit = 2;

    int range = sequenceSize - 1;


    int sizeA = randomNumber(minLimit, maxLimit);
    int sizeB = randomNumber(minLimit, maxLimit);

    int firstPossiblePosA = 1;
    int lastPossiblePosA = range - sizeA - sizeB + 1;


    int posA = randomNumber(firstPossiblePosA, lastPossiblePosA);

    int firstPossiblePosB = posA + sizeA;
    int lastPossiblePosB = range - sizeB + 1;

    int posB = randomNumber(firstPossiblePosB, lastPossiblePosB);


    double delta = calculatePerturbationCost(solution->sequence, posA, sizeA, posB, sizeB, adjacencyMatrix);

    Solution newSolution = *solution;
    newSolution.cost += delta;


    int smallestSegment = std::min(sizeA, sizeB);

    for (int i = 0; i < smallestSegment; ++i)
    {
        std::swap(newSolution.sequence[posA + i], newSolution.sequence[posB + i]);
    }


    int sizeDifference = std::abs(sizeA - sizeB);

    std::vector<int> remainingSegment(sizeDifference);

    if (sizeA > sizeB)
    {
        for (int i = 0; i < sizeDifference; ++i)
        {
            remainingSegment[i] = newSolution.sequence[posA + sizeB + i];
        }

        for (int i = posA + sizeA; i < posB + sizeB; i++)
        {
            newSolution.sequence[i - sizeDifference] = newSolution.sequence[i];
        }

        for (int i = 0; i < sizeDifference; ++i)
        {
            newSolution.sequence[posB + sizeB - sizeDifference + i] = remainingSegment[i];
        }
    }
    else if (sizeA < sizeB)
    {
        for (int i = 0; i < sizeDifference; ++i)
        {
            remainingSegment[i] = newSolution.sequence[posB + sizeA + i];
        }

        for (int i = posB + sizeA - 1; i >= posA + sizeA ; i--)
        {
            newSolution.sequence[i + sizeDifference] = newSolution.sequence[i];
        }

        for (int i = 0; i < sizeDifference; ++i)
        {
            newSolution.sequence[posA + sizeA + i] = remainingSegment[i];
        }
    }
    return newSolution;
}

double calculatePerturbationCost(
    std::vector<int> &sequence, int posA, int sizeA, int posB, int sizeB, double **adjacencyMatrix)
{
    int vertex_posA = sequence[posA];
    int vertex_posA_prev = sequence[posA-1];
    int vertex_posA_last = sequence[posA+sizeA-1];

    int vertex_posB = sequence[posB];
    int vertex_posB_last = sequence[posB+sizeB-1];
    int vertex_posB_last_next = sequence[posB+sizeB];

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
        int vertex_posA_last_next = sequence[posA+sizeA];
        int vertex_posB_prev = sequence[posB-1];
        
        currentCost = adjacencyMatrix[vertex_posA_prev][vertex_posA]
                    + adjacencyMatrix[vertex_posA_last][vertex_posA_last_next]
                    + adjacencyMatrix[vertex_posB_prev][vertex_posB]
                    + adjacencyMatrix[vertex_posB_last][vertex_posB_last_next];

        perturbationCost = adjacencyMatrix[vertex_posB_prev][vertex_posA] 
                         + adjacencyMatrix[vertex_posA_last][vertex_posB_last_next] 
                         + adjacencyMatrix[vertex_posA_prev][vertex_posB] 
                         + adjacencyMatrix[vertex_posB_last][vertex_posA_last_next]; 
    }
    return perturbationCost - currentCost;
}

int randomNumber(int minLimit, int maxLimit)
{
    if (minLimit == maxLimit)
    {
        return minLimit;
    }

    return minLimit + (std::rand() % (maxLimit - minLimit));
}
