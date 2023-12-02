#pragma once 

#ifndef PERTUBATION_HPP
#define PERTUBATION_HPP

#include <vector>

#include "solution.hpp"
#include "construction.hpp"

Solution perturbation(Solution &solution, double **adjacencyMatrix);

#endif