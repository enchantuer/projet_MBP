#ifndef PROJET_MBP_GRAPH_H
#define PROJET_MBP_GRAPH_H

#define ADJ_LIST
//#define ADJ_MATRIX

#include <iostream>
#include <utility>
#include <string>
#include <queue>
#include <stack>

using namespace std;

class Graph {
private:
#ifdef ADJ_LIST
    vector<vector<int>> successor;
    vector<vector<int>> predecessor;
#endif
#ifdef ADJ_MATRIX
    vector<vector<int>> matrix;
#endif
    int n;
    int m;
public:
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
    // BFS
    vector<int> BFSMain(int from=0, bool connected=false);
    void BFSVisit(int v, vector<int> &colors, vector<int> &parents, vector<int> &postPre);
    // DFS
    vector<int> DFSMain(int from=0, bool returnPost=true, bool connected=false);
    void DFSVisit(int v, vector<int> &colors, vector<int> &parents, vector<int> &pre, vector<int> &post);
    // Constructive heuristic
    vector<vector<int>> constructiveHeuristic();
    int getNumberOfEdgesLinkingTwoGroups(vector<int> &group1, vector<int> &group2);
    //Exact
    vector<vector<int>> exactAlgorithm();
    void exactAlgorithmVisit(int &min, vector<int> &A, vector<int> &B, int i, vector<vector<int>> &result);
};


#endif //PROJET_MBP_GRAPH_H