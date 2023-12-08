#pragma once 

#ifndef PERTUBATION_HPP
#define PERTUBATION_HPP

#include <vector>
#include <cmath>
#include <cstdlib> 

#include "solution.hpp"

Solution perturbation(Solution *solution, double **adjacencyMatrix);

#endif