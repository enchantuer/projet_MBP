#include "tabu_search.h"

#include "../algo.h"

// Meta-heuristic
vector<vector<int>> generateRandomSolution(Graph &G) {
    vector<int> randomOrdering(G.n);
    for (int i = 0 ; i < G.n ; i++) {
        randomOrdering[i] = i;
    }
    shuffle(randomOrdering.begin(), randomOrdering.end(), std::mt19937(std::random_device()()));

    vector<int> group1, group2;
    for (int i = 0 ; i < G.n ; i++){
        if (i < G.n/2){
            group1.push_back(randomOrdering[i]);
        }
        else{
            group2.push_back(randomOrdering[i]);
        }
    }

    return {group1, group2};
}

// metaheuristic
vector<vector<int>> metaheuristic(Graph &G, int iter_max, int nb_fail_max){
    vector<vector<int>> constructive = constructiveHeuristic(G);
    vector<vector<int>> bestSolution = localHeuristic(G, constructive);
    int bestCost = G.getNumberOfEdgesLinkingTwoGroups(bestSolution[0], bestSolution[1]);

    // Tabu list for ban groups
    vector<pair<vector<int>, vector<int>>> tabuList;

    int iter = 0;
    int nb_fail = 0;
    while (iter < iter_max && nb_fail < nb_fail_max){
        vector<vector<int>> randomSolution = generateRandomSolution(G);
        int currentCost = G.getNumberOfEdgesLinkingTwoGroups(randomSolution[0], randomSolution[1]);

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
            vector<vector<int>> optimised_random_solution = localHeuristic(G, randomSolution);
            // Add the solution to the tabu list
            // Sort the solution to be able to compare it with the tabu list
            sort(optimised_random_solution[0].begin(), optimised_random_solution[0].end());
            if (randomSolution[0] < optimised_random_solution[0]) {
                tabuList.push_back({randomSolution[0], optimised_random_solution[0]});
            } else {
                tabuList.push_back({optimised_random_solution[0], randomSolution[0]});
            }
            randomSolution = optimised_random_solution;
            currentCost = G.getNumberOfEdgesLinkingTwoGroups(randomSolution[0], randomSolution[1]);
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