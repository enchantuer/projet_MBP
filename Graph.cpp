#include "Graph.h"

#include <algorithm>
#include <random>

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
Graph::Graph(string instance){
    ifstream inputFile(instance);
    if (!inputFile.is_open()) {
        return;
    }
    string line;
    getline(inputFile, line);
    istringstream iss(line);
    int n, m;
    iss >> n >> m;
    this->n = n;
    this->m = 0;
    this->successor = vector<vector<int>>(n);
    this->predecessor = vector<vector<int>>(n);

    getline(inputFile, line);
    istringstream iss2(line);
    int u, v;
    while (iss2 >> u >> v) {
        addEdge(u,v);
        iss2.ignore(2, ' ');
    }
    inputFile.close();
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
        result = constructiveHeuristic();
        result = localHeuristic(result);
    }else {
        string file_name = instancepath + "_meta_search.out";
        file.open(file_name);
        result = metaheuristic(500, 200);    //TODO  Mettre meta
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
            if (result[1].size() == n/2) {
                result[0].push_back(degrees[i].second);
            }
            else {
                if (edges0 >= edges1 && result[0].size() < n/2) {
                    result[0].push_back(degrees[i].second);
                    int count = 0;
                    int deg = degrees[i].first;
                    int j = n-1;
                    while (j > i && count < deg/2) {
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
                    while (j > i && count < deg/2) {
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
            }
            used[degrees[i].second] = true;
        }
    }
    return result;
}

// Local //
vector<vector<int>> Graph::localHeuristic(vector<vector<int>> &solution){;
    vector<int> result0 = solution[0];
    vector<int> result1 = solution[1];
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
            if (best != -1){
                var2 = result0[i];
                result0[i] = result1[j];
                result1[j] = var2;
            }
        }

        if(NM1>best){
            lire = true;
        }
    }
    return {result0, result1};
}




// Meta-heuristic //
vector<vector<int>> Graph::generateRandomSolution() {
    vector<int> randomOrdering(n);
    for (int i = 0 ; i < n ; i++) {
        randomOrdering[i] = i;
    }
    shuffle(randomOrdering.begin(), randomOrdering.end(), std::mt19937(std::random_device()()));

    vector<int> group1, group2;
    for (int i = 0 ; i < n ; i++){
        if (i < n/2){
            group1.push_back(randomOrdering[i]);
        }
        else{
            group2.push_back(randomOrdering[i]);
        }
    }

    return {group1, group2};
}

// metaheuristic
vector<vector<int>> Graph::metaheuristic(int iter_max, int nb_fail_max){
    vector<vector<int>> constructive = constructiveHeuristic();
    vector<vector<int>> bestSolution = localHeuristic(constructive);
    int bestCost = getNumberOfEdgesLinkingTwoGroups(bestSolution[0], bestSolution[1]);

    // Tabu list for ban groups
    vector<pair<vector<int>, vector<int>>> tabuList;

    int iter = 0;
    int nb_fail = 0;
    while (iter < iter_max && nb_fail < nb_fail_max){
        vector<vector<int>> randomSolution = generateRandomSolution();
        int currentCost = getNumberOfEdgesLinkingTwoGroups(randomSolution[0], randomSolution[1]);

        // Check if the solution is in the tabu list
        sort(randomSolution[0].begin(), randomSolution[0].end());
        bool isTabu = false;
        for (auto &solutionRange : tabuList){
            if (solutionRange.first >= randomSolution[0] && solutionRange.second <= randomSolution[0]){
                isTabu = true;
                break;
            }
        }

        // If the solution is not in the tabu list, we apply the local search
        if (!isTabu){
            vector<vector<int>> optimised_random_solution = localHeuristic(randomSolution);
            // Add the solution to the tabu list
            // Sort the solution to be able to compare it with the tabu list
            sort(optimised_random_solution[0].begin(), optimised_random_solution[0].end());
            if (randomSolution[0] < optimised_random_solution[0]) {
                tabuList.push_back({randomSolution[0], optimised_random_solution[0]});
            } else {
                tabuList.push_back({optimised_random_solution[0], randomSolution[0]});
            }
            randomSolution = optimised_random_solution;
            currentCost = getNumberOfEdgesLinkingTwoGroups(randomSolution[0], randomSolution[1]);
        }

        if (currentCost < bestCost){
            bestSolution = randomSolution;
            bestCost = currentCost;
            nb_fail = 0;
        }
        else{
            nb_fail ++;
        }

    }

    return bestSolution;
}