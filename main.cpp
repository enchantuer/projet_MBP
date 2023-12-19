#include "Testing.h"

int main() {
    // Set rand seed
    srand(time(nullptr));

    // Run the algos
    int n = 24;     // max size
    vector<float> p = {0.35,0.4,0.45,0.5};   // density
    int nb = 10;     // number of test for each n-size Graph of density p

    vector<pair<pair<int,float>,vector<Graph>>> VGs = Create_Graphs(n,p,nb);

    Run_Algos(VGs,12,p,"exact");

    return 0;
}