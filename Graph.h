#ifndef PROJET_MBP_GRAPH_H
#define PROJET_MBP_GRAPH_H

#include <iostream>
#include <utility>
#include <string>
#include <queue>
#include <stack>
#include <fstream>
#include <sstream>

using namespace std;

class Graph {
public:
    vector<vector<int>> successor;
    vector<vector<int>> predecessor;
    int n;
    int m;
    // Constructor
    Graph(int n=0);
    // Random graph of density d
    Graph(int n, double d);
    // With an instance
    Graph(string instance);
    // Getters
    int getN() const;
    int getM() const;
    // Add vertex and edge
    void addVertex();
    void addEdge(int v, int u, bool isDirected=true);

    void writeSolutions(string instancepath, string algo);

    //Exact
    vector<vector<int>> exactAlgorithm();
    void exactAlgorithmVisit(int &min, vector<int> &A, vector<int> &B, int i, vector<vector<int>> &result);
    // Constructive heuristic
    vector<vector<int>> constructiveHeuristic();
    int getNumberOfEdgesLinkingTwoGroups(vector<int> &group1, vector<int> &group2);
    int getDegree(int v);

    bool isEdge(int v, int w);

    // Local Search heuristic
    vector<vector<int>> localHeuristic(vector<vector<int>> &solution);


    //Meta-heuristics
    vector<vector<int>> generateRandomSolution();
    vector<vector<int>> metaheuristic(int iter_max, int nbfail_max);
};


#endif //PROJET_MBP_GRAPH_H