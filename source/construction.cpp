#include "construction.hpp"

typedef struct InsertionInfo
{
    int insertedVertex;
    int removedEdge;
    double cost;
} InsertionInfo;

bool compareInsertionsByCost(const InsertionInfo& a, const InsertionInfo& b) {
    return a.cost < b.cost;
}

int getRandomNumber(const int &min, const int &max);

std::vector<int> get3RandomVertices(const int &size);

std::vector<int> getCandidateList(const Solution &solution, const int &size);

double calculateInsertionCost(double **adjacencyMatrix, const int &vertex_k, const int &vertex_i, const int &vertex_j);

double getAlpha();

std::vector<InsertionInfo> calculateAllInsertions(
    const Solution &solution, double **adjacencyMatrix, const std::vector<int> &candidateList);


Solution construction(double **adjacencyMatrix, const int &size)
{
    Solution solution;

    solution.sequence = get3RandomVertices(size);
    
    calculateCost(solution, adjacencyMatrix);

    std::vector<int> candidateList = getCandidateList(solution, size);


    while (!candidateList.empty())
    {
        std::vector<InsertionInfo> insertions = calculateAllInsertions(solution, adjacencyMatrix, candidateList);

        std::sort(insertions.begin(), insertions.end(), compareInsertionsByCost);

        int insertionIndex = getRandomNumber(0, std::ceil(getAlpha() * insertions.size()));

        InsertionInfo selectedInsertion = insertions[insertionIndex];

        std::cout << selectedInsertion.insertedVertex << ' ' << selectedInsertion.removedEdge << '\n';

        std::vector<int>::iterator it = solution.sequence.begin() + 1;

        solution.sequence.insert(it + selectedInsertion.removedEdge, selectedInsertion.insertedVertex);
        
        printSolution(solution);

        solution.cost += selectedInsertion.cost;

        candidateList.erase(
            std::remove(candidateList.begin(), candidateList.end(), selectedInsertion.insertedVertex), candidateList.end());
    }

    return solution;
}

double getAlpha()
{
    std::random_device randomDevice;
    std::mt19937 generator(randomDevice());
    std::uniform_real_distribution<> distribuition(0, 1);

    return distribuition(generator);
}

int getRandomNumber(const int &min, const int &max)
{
    std::random_device randomDevice;
    std::mt19937 generator(randomDevice());
    std::uniform_int_distribution<> distribuition(min, max);

    return distribuition(generator);
}

std::vector<int> get3RandomVertices(const int &size)
{
    std::vector<int> randomVertices;

    while (randomVertices.size() < 3)
    {
        int randomVertex = getRandomNumber(0, size-1);

        if (std::find(randomVertices.begin(), randomVertices.end(), randomVertex) == randomVertices.end())
        {
            randomVertices.push_back(randomVertex);
        }
    }

    return randomVertices;
}

std::vector<int> getCandidateList(const Solution &solution, const int &size)
{
    std::vector<int> candidateList;

    for (int i = 0; i < size; i++)
    {
        if (std::find(solution.sequence.begin(), solution.sequence.end(), i) == solution.sequence.end())
        {
            candidateList.push_back(i);
        }
    }

    return candidateList;
}

double calculateInsertionCost(double **adjacencyMatrix, const int &vertex_k, const int &vertex_i, const int &vertex_j) 
{
    return adjacencyMatrix[vertex_i][vertex_k] + adjacencyMatrix[vertex_j][vertex_k] - adjacencyMatrix[vertex_i][vertex_j];
}

std::vector<InsertionInfo> calculateAllInsertions(
    const Solution &solution, double **adjacencyMatrix, const std::vector<int> &candidateList)
{
    size_t solutionSize = solution.sequence.size();

    std::vector<InsertionInfo> insertions((solutionSize-1) * candidateList.size());

    int index = 0, vertex_i, vertex_j;
    
    for (size_t i = 0; i < solutionSize-1; i++)
    {
        vertex_i = solution.sequence[i];
        vertex_j = solution.sequence[i + 1];

        for (const auto &candidate : candidateList)
        {
            insertions[index].cost = calculateInsertionCost(adjacencyMatrix, candidate, vertex_i, vertex_j);
            insertions[index].insertedVertex = candidate;
            insertions[index].removedEdge = i;

            index++;
        }
    }

    return insertions;
}