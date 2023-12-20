//
// Created by Isen-Ouest on 20/12/2023.
//

#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <algorithm>
#include <random>

#include <fstream>
#include <iostream>
#include <iomanip>


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
    // Getters
    int getN() const;
    int getM() const;
    // Add vertex and edge
    void addVertex();
    void addEdge(int v, int u, bool isDirected=true);
    int getNumberOfEdgesLinkingTwoGroups(vector<int> &group1, vector<int> &group2);
    int getDegree(int v);

    bool isEdge(int v, int w);
};

vector<pair<pair<int,float>,vector<Graph>>> loadGraphs(int n, int nb, vector<float> &p);

#endif //GRAPH_H
