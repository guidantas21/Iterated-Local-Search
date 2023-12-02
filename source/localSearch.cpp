#include "localSearch.hpp"


bool bestImprovementSwap(Solution &solution, double **adjacencyMatrix);

void executeSwap(std::vector<int> &sequence, int best_i, int best_j);

double calculateSwapCost(std::vector<int> &sequence, int i, int j, double **adjacencyMatrix);


bool bestImprovement2OPT(Solution &solution, double **adjacencyMatrix);

void execute2OPT(std::vector<int> &sequence, int start, int end);

double calculate2OPTCost(std::vector<int> &sequence, int start, int end, double **adjacencyMatrix);


bool bestImprovementOROPT(Solution &solution, int n, double **adjacencyMatrix);

void executeOROPT(Solution &solution, int initial, int destiny, int n);

double calculateOROPTCost(Solution &solution, int initial, int destiny, int n, double **adjacencyMatrix);



void localSearch(Solution &solution, double **adjacencyMatrix)
{
    std::vector<int> neighborsList = { 1, 2, 3, 4, 5 };
    bool improved = false;

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

bool bestImprovementSwap(Solution &solution, double **adjacencyMatrix)
{
    double bestDelta = 0;
    int best_i = 0, best_j = 0;

    size_t range = solution.sequence.size() - 1;

    for (size_t i = 1; i < range; i++)
    {
        for (size_t j = i + 1; j < range; j++)
        {
            double delta = calculateSwapCost(solution.sequence, i, j, adjacencyMatrix);

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
        executeSwap(solution.sequence, best_i, best_j);
        solution.cost += bestDelta;

        return true;
    }

    return false;
}

double calculateSwapCost(std::vector<int> &sequence, int i, int j, double **adjacencyMatrix)
{
    int vertex_i = sequence[i];
    int vertex_i_prev = sequence[i-1];

    int vertex_j = sequence[j];
    int vertex_j_next = sequence[j+1];
    
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
        int vertex_i_next = sequence[i+1];
        int vertex_j_prev = sequence[j-1];

        // (|v_i_prev|v_i| + |v_i|v_i_next|) + (|v_j_prev|v_j| + |v_j|v_j_next|)
        currentCost = adjacencyMatrix[vertex_i_prev][vertex_i] + adjacencyMatrix[vertex_i][vertex_i_next]
                    + adjacencyMatrix[vertex_j_prev][vertex_j] + adjacencyMatrix[vertex_j][vertex_j_next];

        // (|v_i_prev|v_j| + |v_j|v_i_next|) + (|v_j_prev|v_i| + |v_i|v_j_next|)
        swapCost = adjacencyMatrix[vertex_i_prev][vertex_j] + adjacencyMatrix[vertex_j][vertex_i_next]
                 + adjacencyMatrix[vertex_j_prev][vertex_i] + adjacencyMatrix[vertex_i][vertex_j_next];
    }

    return swapCost - currentCost;
}

void executeSwap(std::vector<int> &sequence, int best_i, int best_j)
{
    std::swap(sequence[best_i], sequence[best_j]);
}



bool bestImprovement2OPT(Solution &solution, double **adjacencyMatrix)
{
    double bestDelta = 0;
    int bestStart = 0, bestEnd = 0;

    size_t range = solution.sequence.size() - 1;

    for (size_t start = 0; start < range - 1; start++)
    {
        for (size_t end = start + 1; end < range; end++)
        {
            double delta = calculate2OPTCost(solution.sequence, start, end, adjacencyMatrix);
            
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
        execute2OPT(solution.sequence, bestStart, bestEnd);

        solution.cost += bestDelta;

        return true;
    }

    return false;
}

double calculate2OPTCost(std::vector<int> &sequence, int start, int end, double **adjacencyMatrix)
{
    int vertex_start = sequence[start];
    int vertex_start_next = sequence[start+1];

    int vertex_end = sequence[end];
    int vertex_end_next = sequence[end+1];

    // 1, ..., <start>, <start+1>, ... ,  <end>, <end+1>, ..., 1
    double currentCost = adjacencyMatrix[vertex_start][vertex_start_next]
                       + adjacencyMatrix[vertex_end][vertex_end_next];

    // 1, ..., <start+1>, <end+1>, ... ,  <start>, <end>, ..., 1
    double _2OPTCost = adjacencyMatrix[vertex_start_next][vertex_end_next] 
                     + adjacencyMatrix[vertex_start][vertex_end];

    return _2OPTCost - currentCost;
}

void execute2OPT(std::vector<int> &sequence, int start, int end)
{
    std::reverse(sequence.begin() + start + 1, sequence.begin() + end + 1);
}



void executeOROPT(Solution &solution, int initial, int destiny, int n) {
    std::vector<int> segment(n);

    for (int i = 0; i < n; i++)
    {
        segment[i] = solution.sequence[initial + i];
    }	
    
    if (initial < destiny)
    {
        for (int i = initial + n; i <= destiny; i++)
        {
            solution.sequence[i-n] = solution.sequence[i];
        }

        for (int i = 0; i < n; i++)
        {
            solution.sequence[destiny - n + i + 1] = segment[i];
        }
    } 
    else 
    {
        for (int i = initial - 1; i > destiny; i--)
        {
            solution.sequence[i + n] = solution.sequence[i];
        }

        for (int i = 0; i < n; i++)
        {
            solution.sequence[destiny + i + 1] = segment[i];
        }
    }
}

double calculateOROPTCost(Solution &solution, int initial, int destiny, int n, double **adjacencyMatrix)
{
    double currentCost = adjacencyMatrix[solution.sequence[initial-1]][solution.sequence[initial]] 
                       + adjacencyMatrix[solution.sequence[initial+n-1]][solution.sequence[initial+n]]
                       + adjacencyMatrix[solution.sequence[destiny]][solution.sequence[destiny+1]];

    double swapCost = adjacencyMatrix[solution.sequence[initial-1]][solution.sequence[initial+n]] 
                    + adjacencyMatrix[solution.sequence[destiny]][solution.sequence[initial]]
                    + adjacencyMatrix[solution.sequence[initial+n-1]][solution.sequence[destiny+1]];

    return swapCost - currentCost;
}

bool bestImprovementOROPT(Solution &solution, int n, double **adjacencyMatrix)
{
    double bestDelta = 0;
    int bestInitial = 0, bestDestiny = 0;
    
    for (size_t initial = 1; initial < solution.sequence.size() - n; initial++)
    {
        for (size_t destiny = initial + n; destiny < solution.sequence.size() - n; destiny++)
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
        solution.cost += bestDelta;

        return true;
    }

    return false;
}