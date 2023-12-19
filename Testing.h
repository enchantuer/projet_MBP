#ifndef PROJETTEST_TESTING_H
#define PROJETTEST_TESTING_H

#include "Graph.h"

#include <chrono>
vector<pair<pair<int,float>,vector<Graph>>> Create_Graphs(int n, vector<float> p, int nb);

void Run_Algos(vector<pair<pair<int,float>,vector<Graph>>> VGs, int n, vector<float> p , string algo, int nb);


#endif //PROJETTEST_TESTING_H
