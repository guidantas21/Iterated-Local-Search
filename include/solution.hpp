#pragma once 

#ifndef SOLUTION_HPP
#define SOLUTION_HPP

#include <iostream>
#include <vector>
#include <unordered_set>

struct Solution 
{
    std::vector<int> sequence;
    double cost;
};

void printSolution(const Solution &solution);

void calculateCost(Solution &solution, double **adjacencyMatrix);

bool isValid(const Solution &solution, const size_t &size);

#endif