#include "test/Testing.h"
#include "src/model/Graph.h"


int main() {
    // Set rand seed
    srand(time(nullptr));
    // Initialize parameters
    int n = 200;     // max size
    vector<float> p = {0.25,0.5,0.75};   // density
    int nb = 10;     // number of test maximum for each n-size Graph of density p
    // Generate graphs and save them
    /*vector<pair<pair<int,float>,vector<Graph>>> VGs = Create_Graphs(n,p,nb);
    saveVGS(VGs);*/
    // Load graphs from file
    vector<pair<pair<int,float>,vector<Graph>>> VGs = loadGraphs(n, nb, p);
    // Run algorithms
    //Run_Algos(VGs,28,p,"constructive",10);
    //Run_Algos(VGs,28,p,"local_search",10);
    //Run_Algos(VGs,28,p,"tabu_search",10);
    //Run_Algos(VGs,28,p,"exact",10);

    // Test with one instance
    Test_With_Instance("../instances/test1.in", "exact");

    cout<<"goog"<<endl;

    return 0;
}
