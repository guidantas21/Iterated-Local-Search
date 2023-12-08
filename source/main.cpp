#include <iostream>
#include <vector>
#include <chrono>
#include <iomanip>
#include <cstdlib>
#include <ctime> 

#include "ILS.hpp"
#include "solution.hpp"
#include "data.hpp"

struct IlsExecution {
    Solution solution;
    float durationSeconds;
    bool status;
};

struct Result {
    float averageCost;
    float averageDurationSeconds;
    bool status;
};

void printExecutionInfo(IlsExecution &execution);

void printResult(Result &result);

int main(int argc, char** argv)
{
    std::srand(std::time(0));

    ////////// LOAD DATA //////////

    auto data = Data(argc, argv[1]);

    std::cout << "-- Reading Data\n"; 
    data.read();

    const size_t SIZE = data.getDimension();

    int MAX_ITERATIONS = 50;
    int MAX_ITERATIONS_ILS = SIZE >= 150 ? SIZE/2 : SIZE;

    data.printMatrixDist();

    ////////// ILS EXECUTION //////////

    const size_t NUMBER_OF_EXECUTIONS = 10;

    std::vector<IlsExecution> executions(NUMBER_OF_EXECUTIONS);

    float sumCost = 0, sumAverageDurantionSeconds = 0;

    Result result;
    result.status = true;

    IlsExecution ilsExecution;

    for (size_t i = 0; i < NUMBER_OF_EXECUTIONS; ++i)
    {
        std::cout << "\nExecuting ILS... (" << data.getInstanceName() << "[" << i <<"])\n"; 

        auto startTimer = std::chrono::high_resolution_clock::now();

        ilsExecution.solution = ILS(data.getMatrixCost(), SIZE, MAX_ITERATIONS, MAX_ITERATIONS_ILS);

        auto stopTimer = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stopTimer - startTimer);

        ilsExecution.durationSeconds = (float) duration.count() / 1000000.0f;
        ilsExecution.status = isValid(ilsExecution.solution, SIZE, data.getMatrixCost());

        executions[i] = ilsExecution;



        sumAverageDurantionSeconds += ilsExecution.durationSeconds;
        sumCost += ilsExecution.solution.cost;

        if (ilsExecution.status == false)
        {
            result.status = false;
        }


        std::cout << "\n-- Solution (" << data.getInstanceName() << "[" << i <<"])" << std::endl; 

        printExecutionInfo(ilsExecution);
    }

    ////////// RESULT //////////

    result.averageCost = (float) sumCost / NUMBER_OF_EXECUTIONS;
    result.averageDurationSeconds = (float) sumAverageDurantionSeconds / NUMBER_OF_EXECUTIONS;

    std::cout << "\n-- Average result (" << data.getInstanceName() << "):" << std::endl;

    printResult(result);

    saveResults();

    return 0;
}

void printExecutionInfo(IlsExecution &execution)
{
    std::cout << "\nBest tour of all:\n";
    printSolution(execution.solution);
    std::cout << std::endl;
    std::cout << "Solution cost: " << execution.solution.cost << std::endl;
    std::cout << "ILS execution duration: " << execution.durationSeconds << " seconds\n";
    std::cout << "Status: " << (!execution.status ? "IN" : "") << "VALID SOLUTION\n";
}

void printResult(Result &result)
{
    std::cout << "\nAverage solution cost: " << result.averageCost << std::endl;
    std::cout << "Average ILS execution duration: " << result.averageDurationSeconds << " seconds\n";
    std::cout << "Status: " << (!result.status ? "IN" : "") << "VALID SOLUTIONS\n";
}

void saveResults(Result &result, std::string &name, const size_t size)
{
    
}