#pragma once 

#ifndef CONSTRUCTION_HPP
#define CONSTRUCTION_HPP

#include <vector>
#include <unordered_set>
#include <algorithm>
#include <iostream>
#include <cstdlib>
#include <cmath>
#include <random>

#include "solution.hpp"


Solution construction(double **adjacencyMatrix, const size_t &size);

int getRandomNumber(const int &min, const int &max);

#endif