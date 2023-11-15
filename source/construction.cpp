#include "construction.hpp"

struct Insertion
{
    int insertedVertex;
    int removedEdge;
    double cost;
};

bool compareInsertionsByCost(const Insertion& a, const Insertion& b) { return a.cost < b.cost; }

int getRandomNumber(const int &min, const int &max);

double getRandomDouble(const int &min, const int &max);

std::vector<int> get3RandomVertices(std::vector<int> &candidateList);



std::vector<Insertion> calculateInsertion(
    double **adjacencyMatrix, const Solution &solution, const std::vector<int> &candidateList);


Solution construction(double **adjacencyMatrix, const size_t &size) 
{
    Solution solution;

    std::vector<int> candidateList(size-1);

    for (size_t i = 0; i < candidateList.size(); i++)
    {
        candidateList[i] = i+1;
    }

    solution.sequence = get3RandomVertices(candidateList);

    while (!candidateList.empty())
    {
        std::vector<Insertion> insertions = calculateInsertion(adjacencyMatrix, solution, candidateList);
    
        std::sort(insertions.begin(), insertions.end(), compareInsertionsByCost);

        double alpha = getRandomDouble(0,1);
    
        int selectedIndex = getRandomNumber(0, (int) std::floor(alpha * insertions.size()));
    
        solution.sequence.insert(
            solution.sequence.begin()+insertions[selectedIndex].removedEdge+1, insertions[selectedIndex].insertedVertex);

        candidateList.erase(
            std::remove(candidateList.begin(), candidateList.end(), insertions[selectedIndex].insertedVertex), candidateList.end());
        
        insertions.clear();
    }

    return solution;
}

int getRandomNumber(const int &min, const int &max)
{
    std::random_device randomDevice;
    std::mt19937 generator(randomDevice());
    std::uniform_int_distribution<> distribuition(min, max); // [min, max]

    return distribuition(generator);
}

double getRandomDouble(const int &min, const int &max)
{
    std::random_device randomDevice;
    std::mt19937 generator(randomDevice());
    std::uniform_real_distribution<> distribuition(min, max); // [min, max]

    return distribuition(generator);
}

std::vector<int> get3RandomVertices(std::vector<int> &candidateList) 
{
    std::vector<int> vertices(5);

    vertices[0] = 0;
    vertices[4] = 0;

    int vertexIndex;    

    for (int i = 1; i < 4; i++)
    {
        vertexIndex = getRandomNumber(1, candidateList.size()-1);
        vertices[i] = candidateList[vertexIndex];
        candidateList.erase(candidateList.begin() + vertexIndex);
    }

    return vertices;
}

std::vector<Insertion> calculateInsertion(
    double **adjacencyMatrix, const Solution &solution, const std::vector<int> &candidateList)
{   
    std::vector<Insertion> insertions;
    insertions.reserve((solution.sequence.size() - 1) * candidateList.size());

    for (size_t edge = 0; edge < solution.sequence.size()-1; edge++)
    {
        int i = solution.sequence[edge];
        int j = solution.sequence[edge+1];

        for (const int &k : candidateList)
        {
            Insertion insertion;
            insertion.cost = adjacencyMatrix[i][k] + adjacencyMatrix[k][j] - adjacencyMatrix[i][j];
            insertion.insertedVertex = k;
            insertion.removedEdge = edge;

            insertions.push_back(insertion);
        }
    }

    return insertions;
}