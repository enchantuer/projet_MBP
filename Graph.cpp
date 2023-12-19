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


void Graph::writeSolutions(string instancepath, string algo){
    ofstream file;
    vector<vector<int>> result;
    if(algo=="exact"){
        string file_name = instancepath + "_exact.out";
        file.open(file_name);
        result = exactAlgorithm();
    }else if(algo=="constructive"){
        string file_name = instancepath + "_constructive.out";
        file.open(file_name);
        result = constructiveHeuristic();
    }else if(algo=="exact"){
        string file_name = instancepath + "_local_search.out";
        file.open(file_name);
        result = localHeuristic();
    }else {
        string file_name = instancepath + "_meta_search.out";
        file.open(file_name);
        result = localHeuristic();    //TODO  Mettre meta
    }

    int nbedges = getNumberOfEdgesLinkingTwoGroups(result[0], result[1]);
    file << this->n << " " << nbedges << endl;
    for(int i=0; i<result[0].size(); i++){
        file << result[0][i] << " ";
    }
    file << endl;
    for(int i=0; i<result[1].size(); i++){
        file << result[1][i] << " ";
    }
    file << endl;
    file.close();
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

// Exact //
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
    result[0]=Am;
    result[1]=Bm;
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

// Constructive //
vector<vector<int>> Graph::constructiveHeuristic() {
    vector<vector<int>> result(2);
    vector<pair<int, int>> degrees(n);
    vector<bool> used(n);
    for(int i = 0; i < n; i++) {
        degrees.emplace_back(getDegree(i), i);
        used[i] = false;
    }
    sort(degrees.rbegin(), degrees.rend());
    for(int i = 0; i < n; i++) {
        if(!used[degrees[i].second]) {
            vector<int> g = {degrees[i].second};
            int edges0 = getNumberOfEdgesLinkingTwoGroups(result[0], g);
            int edges1 = getNumberOfEdgesLinkingTwoGroups(result[1], g);
            if (result[1].size() >= n/2) {
                result[0].push_back(degrees[i].second);
            }
            else if (result[0].size() < n/2) {
                if (edges0 <= edges1) {
                    result[0].push_back(degrees[i].second);
                    int count = 0;
                    int deg = degrees[i].first;
                    int j = n-1;
                    while (j > i && count < deg/2+1) {
                        if (result[1].size() < n/2  && !used[degrees[j].second]) {
                            if (!isEdge(degrees[i].second, degrees[j].second)) {
                                result[1].push_back(degrees[j].second);
                                count ++;
                                used[degrees[j].second] = true;
                            }
                        }
                        j --;
                    }
                } else {
                    result[1].push_back(degrees[i].second);
                    int count = 0;
                    int deg = degrees[i].first;
                    int j = n-1;
                    while (j > i && count < deg/2+1) {
                        if (result[0].size() < n/2 && !used[degrees[j].second]) {
                            if (!isEdge(degrees[i].second, degrees[j].second)) {
                                result[0].push_back(degrees[j].second);
                                count ++;
                                used[degrees[j].second] = true;
                            }
                        }
                        j --;
                    }
                }
            } else {
                result[1].push_back(degrees[i].second);
            }
            used[degrees[i].second] = true;
        }
    }
    return result;
}

// Local //
vector<vector<int>> Graph::localHeuristic(){
    vector<vector<int>> result = constructiveHeuristic();
    vector<int> result0 = result[0];
    vector<int> result1 = result[1];
    int var,var2;
    int i = 0;
    int j = 0;

    int best=-1;
    int NM1 = getNumberOfEdgesLinkingTwoGroups(result0, result1);
    bool lire = false;
    while(!lire){

        for(int k=0; k<result0.size(); k++){
            for(int w = 0 ; w<result1.size(); w++){
                var = result0[k];
                result0[k] = result1[w];
                result1[w] = var;

                if(getNumberOfEdgesLinkingTwoGroups(result0, result1) < NM1){
                    best = getNumberOfEdgesLinkingTwoGroups(result0, result1);
                    i = k ;
                    j = w ;
                }
                var = result0[k];
                result0[k] = result1[w];
                result1[w] = var;
            }
            var2 = result0[i];
            result0[i] = result1[j];
            result1[j] = var2;
        }

        if(NM1<best){
            lire = false;
        }
        else{
            lire = true;
        }
    }
    result[0]=result0;
    result[1]=result1;
    return result;
}
