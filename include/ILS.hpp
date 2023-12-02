#pragma once 

#ifndef ILS_HPP
#define ILS_HPP

#include <vector>
#include <limits>

#include "solution.hpp"
#include "construction.hpp"
#include "localSearch.hpp"  
#include "perturbation.hpp"


Solution ILS(double **adjacencyMatrix, size_t size, int maxIterations, int maxIterationsILS);


#endif