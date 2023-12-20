#ifndef TABU_SEARCH_H
#define TABU_SEARCH_H

#include <vector>
#include <algorithm>
#include <random>

#include "../model/Graph.h"

vector<vector<int>> generateRandomSolution(Graph &G);
vector<vector<int>> metaheuristic(Graph &G, int iter_max, int nb_fail_max);

#endif //TABU_SEARCH_H
