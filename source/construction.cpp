#include "construction.hpp"

struct Insertion
{
    int insertedVertex;
    int removedEdge;
    double cost;
};

std::random_device globalRandomDevice;

bool compareInsertionsByCost(const Insertion& a, const Insertion& b) { return a.cost < b.cost; }

int getRandomNumber(const int &min, const int &max);

double getRandomNumber(const double &min, const double &max);

std::vector<int> get3RandomVertices(std::vector<int> &candidateList);

std::vector<Insertion> calculateInsertions(
    double **adjacencyMatrix, const std::vector<int> &sequence, const std::vector<int> &candidateList);


Solution construction(double **adjacencyMatrix, const size_t &size) 
{
    Solution solution;

    std::vector<int> candidateList(size-1);

    for (size_t i = 0; i < size; i++)
    {
        candidateList[i] = i+1;
    }


    solution.sequence = get3RandomVertices(candidateList);
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

// int getRandomNumber(const int &min, const int &max)
// {
//     std::mt19937 generator(globalRandomDevice());
//     std::uniform_int_distribution<> distribuition(min, max);

//     return distribuition(generator);
// }

// double getRandomNumber(const double &min, const double &max)
// {
//     std::mt19937 generator(globalRandomDevice());
//     std::uniform_real_distribution<> distribuition(min, max);

//     return distribuition(generator);
// }

std::vector<int> get3RandomVertices(std::vector<int> &candidateList) 
{
    std::vector<int> sequence(5);

    sequence[0] = 0;
    sequence[4] = 0;

    int vertexIndex;    

    for (int i = 1; i < 4; i++)
    {
        // vertexIndex = getRandomNumber(1, candidateList.size()-1);
        vertexIndex = (std::rand() % candidateList.size() - 1) + 1;
        sequence[i] = candidateList[vertexIndex];
        candidateList.erase(candidateList.begin() + vertexIndex);
    }
    return sequence;
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