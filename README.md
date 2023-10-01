# Iterated Local Search (ILS)

## Introduction
Implementing the Iterated Local Search (ILS) metaheuristic for solving the Traveling Salesman Problem (TSP). A metaheuristic is a versatile heuristic approach employed for solving a wide range of combinatorial optimization problems. With a single metaheuristic, it becomes feasible to tackle various distinct problems, often necessitating only modest adjustments for each. This approach enables the generation of reasonably good solutions for such problems within a reasonable timeframe.

## Travelling Salesman Problem (TSP)

### General Definition
The Traveling Salesman Problem (TSP) is a renowned optimization challenge that tasks us with determining the optimal route, often referred to as a "tour", through a given set of cities. The primary goal is to devise a tour that efficiently visits each city exactly once while minimizing the total distance traveled or the duration required to complete the journey. 

### Case Definition
In this scenario, the Symmetric Traveling Salesman Problem (TSP) is conceptualized as a comprehensive undirected weighted graph. Here, cities are represented as vertices, and the connections between them are depicted as edges. The fundamental aim is to devise an optimal tour, wherein each city is visited exactly once. The optimization objective revolves around minimizing the overall cost of the tour, often measured as the total distance traveled or the sum of weights associated with the edges.

## ILS Framework
The ILS process begins with a set number of iterations, cycling through the same sequence for each iteration. These iterations allow for exploration and refinement of solutions.

### 1. Initial Solution (or Construction):
- Within each iteration, an initial solution is generated using a construction algorithm. This initial solution serves as the starting point for further optimization.

### 2. Local Search:
- After obtaining the initial solution, the ILS algorithm initiates a local search. The local search aims to improve the current solution by iteratively exploring neighboring solutions. If a superior solution with a lower cost is discovered during this process, it replaces the previous best solution within the current iteration.

### 3. Update Best Solution of Iteration:
- If the local search and perturbation phases result in an improved solution (lower cost) compared to the best solution within the current iteration, the new solution becomes the best solution for that iteration.

### 4. Perturbation:
- Following the local search phase, perturbation is applied to the current solution. Perturbation introduces controlled disturbances or changes to the solution. This perturbation step is vital for diversifying the search, potentially escaping local optima.

### 5. Global Best Solution:
- At the conclusion of each iteration, the cost of the best solution from that iteration is compared to the cost of the best solution obtained throughout all iterations. If the best solution from the current iteration demonstrates a lower cost, it replaces the previous global best solution as the overall best solution.

This iterative process continues until all predefined iterations are completed. The ILS framework's strength lies in its ability to iteratively explore and refine solutions, potentially converging toward an optimal or near-optimal solution for combinatorial optimization problems like the Traveling Salesman Problem (TSP).

## Construction

## Local Search

## Pertubation

## How to's

### Prerequisites
Before you begin, ensure you have the following prerequisites installed on your system:

1. **CMake**: You can download CMake from the official website [here](https://cmake.org/download/).

### Compile

1. Navigate to the build directory:

```
cd build
```

2. Run CMake to configure the build process:

```
cmake ..
```

3. Build the project

```
make
```

### Run

1. Navigate to the build directory:

```
cd build
```

2. Execute the compiled binary from passing the path of the desired TSP instance

```
./Iterated-Local-Search ../instances/<instance name>.tsp
```

- Example: ```./Iterated-Local-Search ../instances/a280.tsp```

## References
- https://github.com/cvneves/kit-opt/tree/master/GILS-RVND-TSP
- http://comopt.ifi.uni-heidelberg.de/software/TSPLIB95/STSP.html
