#include "localSearch.hpp"

bool bestImprovementSwap(Solution *solution, double **adjacencyMatrix);


bool bestImprovement2OPT(Solution *solution, double **adjacencyMatrix);

void execute2OPT(Solution *solution, int start, int end);

double calculate2OPTCost(Solution *solution, int start, int end, double **adjacencyMatrix);



bool bestImprovementOROPT(Solution *solution, int n, double **adjacencyMatrix);

void executeOROPT(Solution *solution, int initial, int destiny, int n);

double calculateOROPTCost(Solution *solution, int initial, int destiny, int n, double **adjacencyMatrix);


void localSearch(Solution *solution, double **adjacencyMatrix)
{
    std::vector<int> neighborsList = { 1, 2, 3, 4, 5 };
    bool improved = false;

    // std::cout << solution->cost << '\n';

    while (neighborsList.empty() == false)
    {
        int n = getRandomNumber(0, neighborsList.size()-1);

        switch (neighborsList[n])
        {
            case 1:
                improved = bestImprovementSwap(solution, adjacencyMatrix);
                break;
            case 2:
                improved = bestImprovement2OPT(solution, adjacencyMatrix);
                break;
            case 3:
                improved = bestImprovementOROPT(solution, 1, adjacencyMatrix);
                break;
            case 4:
                improved = bestImprovementOROPT(solution, 2, adjacencyMatrix);
                break;
            case 5:
                improved = bestImprovementOROPT(solution, 3, adjacencyMatrix);
                break;
        }

        if (improved)
        {
            neighborsList = { 1, 2, 3, 4, 5 };
        } 
        else {
            neighborsList.erase(neighborsList.begin() + n);
        }
    }
    return;
}

bool bestImprovementSwap(Solution *solution, double **adjacencyMatrix)
{
    double bestDelta = 0;
    int best_i = 0;
    int best_j = 0;

    for (size_t i = 1; i < solution->sequence.size() - 1; i++)
    {
        int vertex_i = solution->sequence[i];
        int vertex_i_next = solution->sequence[i+1];
        int vertex_i_prev = solution->sequence[i-1];

        for (size_t j = i + 1; j < solution->sequence.size() - 1; j++)
        {
            int vertex_j = solution->sequence[j];
            int vertex_j_next = solution->sequence[j+1];

            double currentCost, swapCost;

            // ...|v_i_prev|v_i|v_j|v_j_next|... -> ...|v_i_prev|v_j|v_i|v_j_next|...
            if (i + 1 == j) 
            {
                // |v_i_prev|v_i| + |v_j|v_j_next|
                currentCost = adjacencyMatrix[vertex_i_prev][vertex_i] + adjacencyMatrix[vertex_j][vertex_j_next];

                // |v_i_prev|v_j| + |v_i|v_j_next|
                swapCost = adjacencyMatrix[vertex_i][vertex_j_next] + adjacencyMatrix[vertex_i_prev][vertex_j];
            } 

            // ...|v_i_prev|v_i|v_i_next|...|v_j_prev|v_j|v_j_next|... -> ...|v_i_prev|v_j|v_i_next|...|v_j_prev|v_i|v_j_next|...
            else 
            {
                int vertex_j_prev = solution->sequence[j-1];

                // (|v_i_prev|v_i| + |v_i|v_i_next|) + (|v_j_prev|v_j| + |v_j|v_j_next|)
                currentCost = (adjacencyMatrix[vertex_i_prev][vertex_i] + adjacencyMatrix[vertex_i][vertex_i_next])
                            + (adjacencyMatrix[vertex_j_prev][vertex_j] + adjacencyMatrix[vertex_j][vertex_j_next]);

                // (|v_i_prev|v_j| + |v_j|v_i_next|) + (|v_j_prev|v_i| + |v_i|v_j_next|)
                swapCost = (adjacencyMatrix[vertex_i_prev][vertex_j] + adjacencyMatrix[vertex_j][vertex_i_next]) 
                         + (adjacencyMatrix[vertex_j_prev][vertex_i] + adjacencyMatrix[vertex_i][vertex_j_next]);
            }

            double delta = swapCost - currentCost;

            if (delta < bestDelta)
            {
                bestDelta = delta;
                best_i = i;
                best_j = j;
            } 
        }
    } 

    if (bestDelta < 0)
    {
        std::swap(solution->sequence[best_i], solution->sequence[best_j]);
        solution->cost += bestDelta;

        return true;
    }

    return false;
}


void execute2OPT(Solution *solution, int start, int end)
{
    std::reverse(solution->sequence.begin() + start + 1, solution->sequence.begin() + end + 1);
}

double calculate2OPTCost(Solution *solution, int start, int end, double **adjacencyMatrix)
{
    // 1, ..., <start>, <start+1>, ... ,  <end>, <end+1>, ..., 1
    double currentCost = adjacencyMatrix[solution->sequence[start]][solution->sequence[start+1]]
                       + adjacencyMatrix[solution->sequence[end]][solution->sequence[end+1]];

    // 1, ..., <start+1>, <end+1>, ... ,  <start>, <end>, ..., 1
    double swapCost = adjacencyMatrix[solution->sequence[start+1]][solution->sequence[end+1]] 
                    + adjacencyMatrix[solution->sequence[start]][solution->sequence[end]];

    return swapCost - currentCost;
}

bool bestImprovement2OPT(Solution *solution, double **adjacencyMatrix)
{
    double bestDelta = 0;
    int bestStart = 0;
    int bestEnd = 0;

    for (size_t start = 0; start < solution->sequence.size() - 2; start++)
    {
        for (size_t end = start + 1; end < solution->sequence.size() - 1; end++)
        {
            double delta = calculate2OPTCost(solution, start, end, adjacencyMatrix);
            
            if (delta < bestDelta)
            {
                bestDelta = delta;
                bestStart = start;
                bestEnd = end;
            }
        }
    }

    if (bestDelta < 0)
    {
        execute2OPT(solution, bestStart, bestEnd);

        solution->cost += bestDelta;

        return true;
    }

    return false;
}

void executeOROPT(Solution *solution, int initial, int destiny, int n) {
    std::vector<int> segment(n);

    for (int i = 0; i < n; i++)
    {
        segment[i] = solution->sequence[initial + i];
    }	
    
    if (initial < destiny)
    {
        for (int i = initial + n; i <= destiny; i++)
        {
            solution->sequence[i-n] = solution->sequence[i];
        }

        for (int i = 0; i < n; i++)
        {
            solution->sequence[destiny - n + i + 1] = segment[i];
        }
    } 
    else 
    {
        for (int i = initial - 1; i > destiny; i--)
        {
            solution->sequence[i + n] = solution->sequence[i];
        }

        for (int i = 0; i < n; i++)
        {
            solution->sequence[destiny + i + 1] = segment[i];
        }
    }
}

double calculateOROPTCost(Solution *solution, int initial, int destiny, int n, double **adjacencyMatrix)
{
    double currentCost = adjacencyMatrix[solution->sequence[initial-1]][solution->sequence[initial]] 
                       + adjacencyMatrix[solution->sequence[initial+n-1]][solution->sequence[initial+n]]
                       + adjacencyMatrix[solution->sequence[destiny]][solution->sequence[destiny+1]];

    double swapCost = adjacencyMatrix[solution->sequence[initial-1]][solution->sequence[initial+n]] 
                    + adjacencyMatrix[solution->sequence[destiny]][solution->sequence[initial]]
                    + adjacencyMatrix[solution->sequence[initial+n-1]][solution->sequence[destiny+1]];

    return swapCost - currentCost;
}

bool bestImprovementOROPT(Solution *solution, int n, double **adjacencyMatrix)
{
    double bestDelta = 0, bestInitial = 0, bestDestiny = 0;
    
    for (size_t initial = 1; initial < solution->sequence.size() - n; initial++)
    {
        for (size_t destiny = initial + n; destiny < solution->sequence.size() - n; destiny++)
        {
            double delta = calculateOROPTCost(solution, initial, destiny, n, adjacencyMatrix);

            if (delta < bestDelta)
            {
                bestDelta = delta;
                bestInitial = initial;
                bestDestiny = destiny;
            } 
        }

        for (size_t destiny = 0; destiny < initial - 1; destiny++)
        {
            double delta = calculateOROPTCost(solution, initial, destiny, n, adjacencyMatrix);

            if (delta < bestDelta)
            {
                bestDelta = delta;
                bestInitial = initial;
                bestDestiny = destiny;
            } 
        }
    } 

    if (bestDelta < 0)
    {
        executeOROPT(solution, bestInitial, bestDestiny, n);
        solution->cost += bestDelta;

        return true;
    }

    return false;
}