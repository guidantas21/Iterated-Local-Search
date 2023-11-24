#pragma once 

#ifndef LOCALSEARCH_HPP
#define LOCALSEARCH_HPP

#include <vector>
#include <algorithm>

#include "solution.hpp"
#include "construction.hpp"

void localSearch(Solution *solution, double **adjacencyMatrix);

#endif