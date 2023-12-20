#ifndef EXACT_H
#define EXACT_H

#include <vector>

#include "../model/Graph.h"

void exactAlgorithmVisit(Graph &G, int &min, vector<int> &A, vector<int> &B, int i, vector<vector<int>> &result);
vector<vector<int>> exactAlgorithm(Graph &G);

#endif //EXACT_H
