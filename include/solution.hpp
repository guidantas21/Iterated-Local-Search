#pragma once 

#ifndef SOLUTION_HPP
#define SOLUTION_HPP

#include <iostream>
#include <vector>

typedef struct Solution 
{
    std::vector<int> sequence;
    double cost;
} Solution;

void printSolution(const Solution &solution);

void calculateCost(Solution &solution, double **adjacencyMatrix);

#endif