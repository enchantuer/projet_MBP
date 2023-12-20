#include "Graph.h"

void Graph::addVertex() {
    n++;
}

void Graph::addEdge(int v, int u, bool isDirected) {
    m++;
    successor[v].push_back(u);
    predecessor[u].push_back(v);
    if(!isDirected) {
        successor[u].push_back(v);
        predecessor[v].push_back(u);
    }
}

Graph::Graph(int n) : n(n), m(0), successor(n), predecessor(n) {}

Graph::Graph(int n, double d) : Graph(n) {
    for(int i=0; i<n-1; i++){
        for(int j=i+1; j<n; j++){
            if(rand()%100 < d*100){
                addEdge(i,j);
            }
        }
    }
}

// Getters
int Graph::getN() const {
    return n;
}
int Graph::getM() const {
    return m;
}
int Graph::getDegree(int v) {
    return successor[v].size() + predecessor[v].size();
}
bool Graph::isEdge(int v, int w) {
    for (int i = 0; i<successor[v].size(); i++) {
        if (successor[v][i]==w) {
            return true;
        }
    }
    for (int i = 0; i<predecessor[v].size(); i++) {
        if (predecessor[v][i]==w) {
            return true;
        }
    }
    return false;
}

int Graph::getNumberOfEdgesLinkingTwoGroups(vector<int> &group1, vector<int> &group2) {
    int result = 0;
    for (auto v : group1) {
        for (auto u : group2) {
            if ((find(successor[v].begin(), successor[v].end(),u) != successor[v].end()) ||(find(successor[u].begin(), successor[u].end(),v) != successor[u].end())) {
                result++;
            }
        }
    }
    return result;
}

vector<pair<pair<int,float>,vector<Graph>>> loadGraphs(int n, int nb, vector<float> &p) {
    vector<pair<pair<int,float>,vector<Graph>>> VGs;
    ifstream instance;
    for (int j = 2; j <= n; j+=2) {
        for (int i = 0; i < p.size(); i++) {
            pair<int,float> np = make_pair(j,p[i]);
            vector<Graph> Vg;
            for (int k = 0; k < nb; ++k) {
                std::stringstream stream;
                stream << std::fixed << std::setprecision(2) << p[i];
                string name = "../instances/new_instances/" + to_string(j) + "_" + stream.str() + "_" + to_string(k) + ".in";
                instance.open(name);
                string line;
                getline(instance, line);
                istringstream iss(line);
                int n, m;
                iss >> n >> m;
                Graph g(n);

                getline(instance, line);
                istringstream iss2(line);
                int u, v;
                while (iss2 >> u >> v) {
                    g.addEdge(u,v);
                    iss2.ignore(2, ' ');
                }
                Vg.push_back(g);
                instance.close();
            }
            VGs.push_back(make_pair(np,Vg));
        }
    }
    return VGs;
}