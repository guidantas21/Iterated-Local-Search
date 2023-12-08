#pragma once 

#ifndef LOCALSEARCH_HPP
#define LOCALSEARCH_HPP

#include <vector>
#include <algorithm>
#include <cmath>
#include <cstdlib> 

#include "solution.hpp"

void localSearch(Solution *solution, double **adjacencyMatrix);

#endif