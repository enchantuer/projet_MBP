# projet_MBP

## How to compile
If you want to execute in Debian, first, you need to move to the project folder. And now you can compile the code using :
```
g++ -Wall main.cpp src/constructive/constructive.cpp src/exact/exact.cpp src/local_search/local_search.cpp src/tabu_search/tabu_search.cpp src/model/Graph.cpp test/Testing.cpp -o projet 
```
## How to execute
To execute the program, use the same name as you use to compile before :
```
./projet
```
## Where to find the executable

## Where to put the inputs files

## Where to find the outputs files

## How to use the program


Algorithm Project for school. Minimum Bisection Problem

This project is a school project for the Graph courses.
The goal is to find the minimum bisection of a graph. To do so, we use three type of algorithm:
- An exact algorithm
- A constructive heuristic algorithm
- A local search heuristic algorithm
- A meta-heuristic algorithm

### Exact algorithm
The exact algorithm is a brute force algorithm.
It will try every possible combination of bisection and return the best one.
Therefor, we implemented an upgrade of the brute force algorithm.
It will try every possible combination of bisection but will stop if the current bisection is worst than the best one found so far.

### Constructive heuristic algorithm
The constructive heuristic algorithm is a greedy algorithm.
It will try to find the best bisection by adding the best node to the best side at each iteration.
By consequence, it will not always find the best bisection but it will be faster than the exact algorithm.

### Local search heuristic algorithm
The local search heuristic algorithm is a greedy algorithm.
It will try to find the best bisection by swapping the worst node of the worst side with the best node of the best side.
By consequence, it will not always find the best bisection but it will be faster than the exact algorithm.

### Meta-heuristic algorithm
The meta-heuristic algorithm is a greedy algorithm.
It will try to find the best bisection by swapping the worst node of the worst side with the best node of the best side.
By consequence, it will not always find the best bisection but it will be faster than the exact algorithm.
We will use the tabu search algorithm to avoid local minimum.