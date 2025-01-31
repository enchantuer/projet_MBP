#ifndef PROJETTEST_TESTING_H
#define PROJETTEST_TESTING_H

#include "../model/Graph.h"
#include "../algo.h"

#include <chrono>
#include <iomanip>
#include <iostream>
#include <vector>
#include <fstream>

using namespace std::chrono;

vector<pair<pair<int,float>,vector<Graph>>> Create_Graphs(int n, vector<float> p, int nb);

void Run_Algos(vector<pair<pair<int,float>,vector<Graph>>> &VGs, int n, vector<float> p , string algo, int nb);

void Test_With_Instance(string instancepath, string algo);

void saveVGS(vector<pair<pair<int,float>,vector<Graph>>> &VGs);

#endif //PROJETTEST_TESTING_H
