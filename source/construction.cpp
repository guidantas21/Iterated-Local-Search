#include "construction.hpp"

struct Insertion
{
    int insertedVertex;
    int removedEdge;
    double cost;
};

std::random_device globalRandomDevice;

bool compareInsertionsByCost(const Insertion& a, const Insertion& b) { return a.cost < b.cost; }

void get3RandomVertices(std::vector<int> &sequence, std::vector<int> &candidateList);

std::vector<Insertion> calculateInsertions(
    double **adjacencyMatrix, const std::vector<int> &sequence, const std::vector<int> &candidateList);


Solution construction(double **adjacencyMatrix, const size_t &size) 
{
    Solution solution;

    std::vector<int> candidateList(size-1);

    // std::cout << "test\n";

    for (size_t i = 0; i < size-1; i++)
    {
        candidateList[i] = i+1;
    }

    get3RandomVertices(solution.sequence, candidateList);
    calculateCost(solution, adjacencyMatrix);


    while (!candidateList.empty())
    {
        std::vector<Insertion> insertions = calculateInsertions(adjacencyMatrix, solution.sequence, candidateList);
    
        std::sort(insertions.begin(), insertions.end(), compareInsertionsByCost);

        double alpha = (double) std::rand() / RAND_MAX;
        int selectedIndex = std::rand() % (int) std::ceil(alpha * insertions.size());

        int insertedVertex = insertions[selectedIndex].insertedVertex;
        auto insertionPos = solution.sequence.begin() + insertions[selectedIndex].removedEdge + 1;

        solution.sequence.insert(insertionPos, insertedVertex);
        solution.cost += insertions[selectedIndex].cost;

        candidateList.erase(
            std::remove(candidateList.begin(), candidateList.end(), insertedVertex), candidateList.end());
    }
    return solution;
}

void get3RandomVertices(std::vector<int> &sequence, std::vector<int> &candidateList) 
{
    sequence.push_back(0);

    int vertexIndex;    

    for (int i = 0; i < 3; i++)
    {
        vertexIndex = std::rand() % candidateList.size();
        sequence.emplace_back(candidateList[vertexIndex]);
        candidateList.erase(candidateList.begin() + vertexIndex);
    }

    sequence.push_back(0);
}

std::vector<Insertion> calculateInsertions(
    double **adjacencyMatrix, const std::vector<int> &sequence, const std::vector<int> &candidateList)
{   
    size_t range = sequence.size() - 1;
    
    std::vector<Insertion> insertions(range * candidateList.size());

    int index = 0;
    for (size_t edge = 0; edge < range; edge++)
    {
        int i = sequence[edge];
        int j = sequence[edge + 1];

        for (const int &k : candidateList)
        {
            insertions[index].cost = adjacencyMatrix[i][k] + adjacencyMatrix[j][k] - adjacencyMatrix[i][j];
            insertions[index].insertedVertex = k;
            insertions[index].removedEdge = edge;

            index++;
        }
    }
    return insertions;
}