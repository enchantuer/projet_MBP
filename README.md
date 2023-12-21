# project_MBP
___
## MBP
Algorithm Project for school. Minimum Bisection Problem

This project is a school project for the Graph courses.
The goal is to find the minimum bisection of a graph. To do so, we use three type of algorithm :
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
By consequence, it will not always find the best bisection, but it will be faster than the exact algorithm.

### Local search heuristic algorithm
The local search heuristic algorithm is an improvement of the constructive heuristic.
It will try to find the best local solution by swapping the worst node of the worst side with the best node of the best side.
By consequence, it will not always find the best bisection, but it will still improve the given solution, usually the constructive heuristic one.

### Meta-heuristic algorithm
The meta-heuristic algorithm is an algorithm that implement random.
It will try to find a new random solution and improve it using local search. If the solution is better than the best one found so far, it will replace it
Since this algorithm use random to try to improve the solution, it might not always find the best solution, or at the cost of more time than the exact algorithm.

___

## Structure
The project structure is organised over 6 part. 
- The source code (c++ code) `src`
- The graphs used and the solutions generated by the program `instances`
- The data generated using the graphs to compare the algorithms `csv`
- The gnuplot scripts used to render those data `scripts`
- The report of the project `report`
- The readme to allow to understand how to use this project `README.md`

`src` contain one folder per algorithm,
plus one folder, named model, for the common function and the Graph class,
as well as one folder for the functions that allow to use the graph to generate data using or not input files
and the file `main.cpp` where you choose what to do.

`instances` contain two things :
- A folder named `new_instances` that contain the graphs we generated and used to generate the data for all our graphics we used in the report.
It allowed use to have consistent data across all test.
Those graph where generated randomly.
- One folder named `algorithm`, for each algorithm (`exact`, `constructive`, `local_search`, `tabu_search`),
that contain graphs to use to generate solutions to the MBP. The generated solutions will also be found in those folders.

`csv` contain all data generated for all our graphics we used in the report.

`script` contain all gnuplot scripts used to generate the graphics for the report using the data from `csv`

`report` contain the report in pdf format
___
## How to compile in Debian
If you want to execute the project in Debian, first, you need to move in your terminal to the project folder using
```
cd path/to/the/project
```

And now you can compile the code using :
```
g++ -Wall src/main.cpp src/constructive/constructive.cpp src/exact/exact.cpp src/local_search/local_search.cpp src/tabu_search/tabu_search.cpp src/model/Graph.cpp src/test/Testing.cpp -o project_MBP
```
The executable file will be created where you are located, so normally at the root of this project
## How to execute
To execute the program, use the same name as you use to compile before after `-o`, in our case project_MBP, precede with `./` :
```
./project_MBP
```
___
## How to use the program
### Where to put the inputs files
You can input files of instances in the directories :

- "instances/exact/"
- "instances/constructive/"
- "instances/local_search/"
- "instances/tabu_search/"
### Where to find the outputs files
You can find the output files at the same place that the input files
___
### Create / Load Graphs: 
#### Create
If you want, you can create a graph. There is three possibilities.

If you want to generate a random graph of probability `p` to have an edge and `n` vertices :
```
Graph g(n,p);
```
If you want to add vertices one by one to a graph of size `n`:
```
Graph g(n);

g.addEdge(0,1);
...
```

#### Load
And if you want to use an input file `.in` of path `path`:
```
Graph g("path/graph.in");
```
___
### Generate data to measure the efficiency:
If you want to generate data in `.csv` file, use `nb` graphs for each probability `p` and each number of vertices `n`. `nb` represent the number of graph per probability and size n to use and get an average result.

#### Random
If you want to create a random set of graphs :
```
vector<pair<pair<int,float>,vector<Graph>>> VGs = Create_Graphs(n,p,nb);
```
##### Save
You have the possibility to save those graphs, to use them again later, using :
```
saveVGS(VGs);
```
It will save them in `instances\new_instances` and overwrite existing files if necessary.

#### Load
If you want to load the existing ones in `instances\new_instances`
Be careful that the already given graphs allow you to have up to `n=200`, `nb=10` and `p={0.75, 0.50, 0.25}`
```
vector<pair<pair<int,float>,vector<Graph>>> VGs = loadGraphs(n, nb, p);
```

#### Generate
Then, you can choose an algorithm to use : "exact" or "constructive" or "local_search" or "tabu_search".

Note that inputting another string will result in using the tabu search.

Note that `n` and `nb` must be smaller or equal to the one used to create `VGs` and `p` must only contain value used to create `VGs`
```
Run_Algos(VGs,n,p,"exact",nb);
```
___
### Generate the result for an input file:
If you want to write an output file `.out` using an input instance file `.in` and a specific algorithm ("exact" or "constructive" or "local_search" or "tabu_search"), use the following command.

Note that the input file `.in` must be located in `instaces\algorithm` with algorithm the one you want to run ("exact" or "constructive" or "local_search" or "tabu_search").

The output file `.out` will be located in the same directory with the same name except than `.in` become `.out`.
```
Test_With_Instance("test1.in", "exact");
```
___