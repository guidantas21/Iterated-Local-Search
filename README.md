# Iterated Local Search (ILS)

## Introduction
Implementing the Iterated Local Search (ILS) metaheuristic for solving the Traveling Salesman Problem (TSP). A metaheuristic is a versatile heuristic approach employed for solving a wide range of combinatorial optimization problems. With a single metaheuristic, it becomes feasible to tackle various distinct problems, often necessitating only modest adjustments for each. This approach enables the generation of reasonably good solutions for such problems within a reasonable timeframe.

## Travelling Salesman Problem (TSP)

### General Definition
The Traveling Salesman Problem (TSP) is a renowned optimization challenge that tasks us with determining the optimal route, often referred to as a "tour", through a given set of cities. The primary goal is to devise a tour that efficiently visits each city exactly once while minimizing the total distance traveled or the duration required to complete the journey. 

### Case Definition
In this scenario, the Symmetric Traveling Salesman Problem (TSP) is conceptualized as a comprehensive undirected weighted graph. Here, cities are represented as vertices, and the connections between them are depicted as edges. The fundamental aim is to devise an optimal tour, wherein each city is visited exactly once. The optimization objective revolves around minimizing the overall cost of the tour, often measured as the total distance traveled or the sum of weights associated with the edges.

## ILS Framework

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
