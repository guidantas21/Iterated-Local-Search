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

void printSolution(Solution& solution);

void calculateObjectiveValue(Solution& solution, double **adjacencyMatrix);

#endif