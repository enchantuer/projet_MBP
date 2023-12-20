#include "exact.h"

// Exact
void exactAlgorithmVisit(Graph &G, int &min, vector<int> &A, vector<int> &B, int i, vector<vector<int>> &result) {
    vector<int> Ab = A;
    vector<int> Bb = B;
    if(i==G.n){
        min = G.getNumberOfEdgesLinkingTwoGroups(A,B);
        result[0] = A;
        result[1] = B;
    }else{
        if(Ab.size()<G.n/2){
            Ab.push_back(i);
            if(min>G.getNumberOfEdgesLinkingTwoGroups(Ab,B)){
                exactAlgorithmVisit(G, min,Ab,B,i+1, result);
            }
        }
        if(Bb.size()<G.n/2){
            Bb.push_back(i);
            if(min>G.getNumberOfEdgesLinkingTwoGroups(A,Bb)){
                exactAlgorithmVisit(G, min,A,Bb,i+1, result);
            }
        }
    }
}

vector<vector<int>> exactAlgorithm(Graph &G) {
    vector<int> Am;
    vector<int> Bm;
    if(G.n%2!=0){
        return {Am,Bm};
    }
    for(int i=0; i<G.n; i++){
        if(i%2==0){
            Am.push_back(i);
        }else{
            Bm.push_back(i);
        }
    }
    int min = G.getNumberOfEdgesLinkingTwoGroups(Am,Bm);
    vector<int> A;
    vector<int> B;
    A.push_back(0);
    vector<vector<int>> result(2);
    result[0]=Am;
    result[1]=Bm;
    exactAlgorithmVisit(G, min, A, B, 1, result);
    return result;
}