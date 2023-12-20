#include "Testing.h"
#include <math.h>

int main() {
    // Set rand seed
    srand(time(nullptr));

    // Run the algos
    int n = 150;     // max size
    vector<float> p = {0.25,0.5,0.75};   // density
    int nb = 10;     // number of test for each n-size Graph of density p

    vector<pair<pair<int,float>,vector<Graph>>> VGs = Create_Graphs(n,p,nb);

    Run_Algos(VGs,18,p,"constructive",5);
    Run_Algos(VGs,18,p,"local_search",5);
    Run_Algos(VGs,18,p,"tabu_search",5);
    Run_Algos(VGs,18,p,"exact",5);

    //Test_With_Instance("../instances/test1.in", "exact");

    /*
    ofstream filetime;
    string file_time = "../csv/exact_time.csv";
    filetime.open(file_time,ios::app);
    for(int nn=2; nn<27;nn+=2){
        auto start = high_resolution_clock::now();
        for (int i = 0; i <= nn*nn*pow(2,nn); ++i) {

        }
        auto stop = high_resolution_clock::now();
        int duration = duration_cast<microseconds>(stop - start).count();
        filetime << nn << ";" << duration << endl;
        cout<<"n: "<< nn << " - d: " << duration<<endl;
    }
     */

    return 0;
}