#include "Graph.h"

#include <algorithm>

void Graph::addVertex() {
    n++;
}

void Graph::addEdge(int v, int u, bool isDirected) {
    m++;
#ifdef ADJ_LIST
    successor[v].push_back(u);
    predecessor[u].push_back(v);
    if(!isDirected) {
        successor[u].push_back(v);
        predecessor[v].push_back(u);
    }
#endif
#ifdef ADJ_MATRIX
    matrix[v][u] = 1;
    if(!isDirected) {
        matrix[u][v] = 1;
    }
#endif
}

vector<int> Graph::BFSMain(int from, bool connected) {
    /* 0 -> Undiscovered
     * 1 -> Discovered
     * 2 -> Done, totally visited
    */
    vector<int> colors(n);
    vector<int> parents(n);
    vector<int> postPre;
    for(int v=0; v<n; v++){
        colors[v] = 0;
        parents[v] = -1;
    }
    BFSVisit(from,colors,parents,postPre);
    if (!connected) {
        for(int v=0; v<n; v++){
            if(colors[v]==0){
                BFSVisit(v,colors,parents,postPre);
            }
        }
    }
    return postPre;
}

#if defined(ADJ_LIST) && !defined(ADJ_MATRIX)
void Graph::BFSVisit(int v, vector<int> &colors, vector<int> &parents, vector<int> &postPre) {
    colors[v] = 1;
    queue<int> Q;
    Q.push(v);
    while(!Q.empty()){
        int u = Q.front();
        Q.pop();
        for (auto w : successor[u]){
            if(colors[w]==0){
                colors[w] = 1;
                parents[w] = u;
                Q.push(w);
            }
        }
        colors[u] = 2;
        postPre.push_back(u);
    }
}
#endif

vector<int> Graph::DFSMain(int from, bool returnPost, bool connected) {
    /* 0 -> Undiscovered
 * 1 -> Discovered
 * 2 -> Done, totally visited
*/
    vector<int> colors(n);
    vector<int> parents(n);
    vector<int> post;
    vector<int> pre;
    for(int v=0; v<n; v++){
        colors[v] = 0;
        parents[v] = -1;
    }
    DFSVisit(from,colors,parents,pre, post);
    if (!connected) {
        for(int v=0; v<n; v++){
            if(colors[v]==0){
                DFSVisit(v,colors,parents,pre, post);
            }
        }
    }
    if(returnPost){
        return post;
    } else {
        return pre;
    }
}

#if defined(ADJ_LIST) && !defined(ADJ_MATRIX)
void Graph::DFSVisit(int v, vector<int> &colors, vector<int> &parents, vector<int> &pre, vector<int> &post) {
    stack<int> s;
    s.push(v);
    while(!s.empty()){
        int u = s.top();
        if(colors[u]==0){
            pre.push_back(u);
            colors[u] = 1;
            for(auto w : successor[u]){
                if(colors[w]==0){
                    parents[w] = u;
                    s.push(w);
                }
            }
        } else if (colors[u]==1){
            colors[u] = 2;
            post.push_back(u);
            s.pop();
        } else {
            s.pop();
        }
    }
}
#endif

#if defined(ADJ_LIST) && !defined(ADJ_MATRIX)
Graph::Graph(int n) : n(n), m(0), successor(n), predecessor(n) {}
#endif

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

vector<vector<int>> Graph::constructiveHeuristic() {
    vector<vector<int>> result(2);

    vector<int> post = DFSMain(0, true, false);
    for(int i = 0; i < post.size(); i++) {
        if(i < n/2) {
            result[0].push_back(post[i]);
        } else {
            result[1].push_back(post[i]);
        }
    }
    return result;
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

vector<vector<int>> Graph::exactAlgorithm(){
    vector<int> Am;
    vector<int> Bm;
    if(this->n%2!=0){
        cout << "error: there is not odd vertices" << endl;
        return {Am,Bm};
    }
    for(int i=0; i<n; i++){
        if(i%2==0){
            Am.push_back(i);
        }else{
            Bm.push_back(i);
        }
    }
    int min = getNumberOfEdgesLinkingTwoGroups(Am,Bm);
    vector<int> A;
    vector<int> B;
    A.push_back(0);
    vector<vector<int>> result(2);
    exactAlgorithmVisit(min, A, B, 1, result);
    return result;
}
void Graph::exactAlgorithmVisit(int &min, vector<int> &A, vector<int> &B, int i, vector<vector<int>> &result){
    vector<int> Ab = A;
    vector<int> Bb = B;
    if(i==n){
        min = getNumberOfEdgesLinkingTwoGroups(A,B);
        result[0] = A;
        result[1] = B;
    }else{
        if(Ab.size()<this->n/2){
            Ab.push_back(i);
            if(min>getNumberOfEdgesLinkingTwoGroups(Ab,B)){
                exactAlgorithmVisit(min,Ab,B,i+1, result);
            }
        }
        if(Bb.size()<this->n/2){
            Bb.push_back(i);
            if(min>getNumberOfEdgesLinkingTwoGroups(A,Bb)){
                exactAlgorithmVisit(min,A,Bb,i+1, result);
            }
        }
    }
}