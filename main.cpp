#include "Graph.h"

int main() {
    // Set rand seed
    srand(time(nullptr));
    // Test
    // Graph 1
    Graph g(5);
    g.addEdge(0,1);
    g.addEdge(0,2);
    g.addEdge(1,3);
    g.addEdge(2,3);
    g.addEdge(3,4);
    g.addEdge(4,0);
    cout << "Graph 1 (n=5)" << endl;
    vector<int> postPre = g.BFSMain(0);
    for (auto v : postPre){
        cout << v << " ";
    }
    cout << endl;
    postPre = g.DFSMain(0, false);
    for (auto v : postPre){
        cout << v << " ";
    }
    cout << endl;
    // Graph 2 (random)
    Graph g2(10, 0.25);
    cout << "Graph 2 (n=5, d=0.3)" << endl;
    cout << "Number of edges : " << g2.getM() << endl;
    postPre = g2.BFSMain(0);
    cout << "BFS" << endl;
    for (auto v : postPre){
        cout << v << " ";
    }
    cout << endl;
    postPre = g2.DFSMain(0, true, true);
    cout << "DFS (only vertices connected to 0)" << endl;
    for (auto v : postPre){
        cout << v << " ";
    }
    cout << endl;
    // Test constructive heuristic
    Graph g3(10, 0.3);
    cout << "Graph 3 (n=10, d=0.3)" << endl;
    cout << "Number of edges : " << g3.getM() << endl;
    vector<vector<int>> result = g3.constructiveHeuristic();
    cout << "Group 1 : ";
    for (auto v : result[0]){
        cout << v << " ";
    }
    cout << endl;
    cout << "Group 2 : ";
    for (auto v : result[1]){
        cout << v << " ";
    }
    cout << endl;
    cout << "Number of edges linking the two groups : " << g3.getNumberOfEdgesLinkingTwoGroups(result[0], result[1]) << endl;

    // Test exact algorithm
    Graph g4(10, 0.3);
    cout << "Graph 4 (n=10, d=0.3)" << endl;
    cout << "Number of edges : " << g4.getM() << endl;
    vector<vector<int>> temp(2);
    vector<vector<int>> result2 = g4.exactAlgorithm();
    cout << "Group 1 : ";
    for (auto v : result2[0]){
        cout << v << " ";
    }
    cout << endl;
    cout << "Group 2 : ";
    for (auto v : result2[1]){
        cout << v << " ";
    }
    cout << endl;
    cout << "Number of edges linking the two groups : " << g4.getNumberOfEdgesLinkingTwoGroups(result2[0], result2[1]) << endl;

    return 0;
}