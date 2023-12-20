#include "local_search.h"

// Local
vector<vector<int>> localHeuristic(Graph &G, vector<vector<int>> &solution) {
    vector<int> result0 = solution[0];
    vector<int> result1 = solution[1];
    int var,var2;
    int i = 0;
    int j = 0;

    int best=-1;
    int NM1 = G.getNumberOfEdgesLinkingTwoGroups(result0, result1);
    bool lire = false;
    while(!lire){

        for(int k=0; k<result0.size(); k++){
            for(int w = 0 ; w<result1.size(); w++){
                var = result0[k];
                result0[k] = result1[w];
                result1[w] = var;

                if(G.getNumberOfEdgesLinkingTwoGroups(result0, result1) < NM1){
                    best = G.getNumberOfEdgesLinkingTwoGroups(result0, result1);
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