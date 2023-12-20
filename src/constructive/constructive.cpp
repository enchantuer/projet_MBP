#include "constructive.h"

// Constructive
vector<vector<int>> constructiveHeuristic(Graph &G) {
    vector<vector<int>> result(2);
    vector<pair<int, int>> degrees(G.n);
    vector<bool> used(G.n);
    for(int i = 0; i < G.n; i++) {
        degrees.emplace_back(G.getDegree(i), i);
        used[i] = false;
    }
    std::sort(degrees.rbegin(), degrees.rend());
    for(int i = 0; i < G.n; i++) {
        if(!used[degrees[i].second]) {
            vector<int> g = {degrees[i].second};
            int edges0 = G.getNumberOfEdgesLinkingTwoGroups(result[0], g);
            int edges1 = G.getNumberOfEdgesLinkingTwoGroups(result[1], g);
            if (result[1].size() == G.n/2) {
                result[0].push_back(degrees[i].second);
            }
            else {
                if (edges0 >= edges1 && result[0].size() < G.n/2) {
                    result[0].push_back(degrees[i].second);
                    int count = 0;
                    int deg = degrees[i].first;
                    int j = G.n-1;
                    while (j > i && count < deg/2) {
                        if (result[1].size() < G.n/2  && !used[degrees[j].second]) {
                            if (!G.isEdge(degrees[i].second, degrees[j].second)) {
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
                    int j = G.n-1;
                    while (j > i && count < deg/2) {
                        if (result[0].size() < G.n/2 && !used[degrees[j].second]) {
                            if (!G.isEdge(degrees[i].second, degrees[j].second)) {
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