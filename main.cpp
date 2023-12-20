#include <iomanip>

#include "Testing.h"

void saveVGS(vector<pair<pair<int,float>,vector<Graph>>> &VGs) {
    ofstream instance;
    for (int i = 0; i < VGs.size(); ++i) {
        for (int j = 0; j < VGs[i].second.size(); ++j) {
            std::stringstream stream;
            stream << std::fixed << std::setprecision(2) << VGs[i].first.second;
            string name = "../instances/new_instances/" + to_string(VGs[i].first.first) + "_" + stream.str() + "_" + to_string(j) + ".in";
            instance.open(name);
            instance << VGs[i].second[j].getN() << " " << VGs[i].second[j].getM() << endl;
            for (int k = 0; k < VGs[i].second[j].getN(); ++k) {
                for (int v : VGs[i].second[j].successor[k]) {
                    instance << k << " " << v << "  ";
                }
            }
            instance.close();
        }
    }
}

int n = 200;     // max size
vector<float> p = {0.25,0.5,0.75};   // density
int nb = 10;     // number of test maximum for each n-size Graph of density p

vector<pair<pair<int,float>,vector<Graph>>> loadGraphs(int n, int nb, vector<float> &p) {
    vector<pair<pair<int,float>,vector<Graph>>> VGs;
    ifstream instance;
    for (int j = 2; j <= n; j+=2) {
        for (int i = 0; i < p.size(); i++) {
            pair<int,float> np = make_pair(j,p[i]);
            vector<Graph> Vg;
            for (int k = 0; k < nb; ++k) {
                std::stringstream stream;
                stream << std::fixed << std::setprecision(2) << p[i];
                string name = "../instances/new_instances/" + to_string(j) + "_" + stream.str() + "_" + to_string(k) + ".in";
                instance.open(name);
                // int n, m;
                // instance >> n >> m;
                // Graph g(n);
                // for (int l = 0; l < m; ++l) {
                //     int v, u;
                //     instance >> v >> u;
                //     g.addEdge(v, u);
                // }
                string line;
                getline(instance, line);
                istringstream iss(line);
                int n, m;
                iss >> n >> m;
                Graph g(n);

                getline(instance, line);
                istringstream iss2(line);
                int u, v;
                while (iss2 >> u >> v) {
                    g.addEdge(u,v);
                    iss2.ignore(2, ' ');
                }
                Vg.push_back(g);
                instance.close();
            }
            VGs.push_back(make_pair(np,Vg));
        }
    }
    return VGs;
}


int main() {
    // Set rand seed
    srand(time(nullptr));

    // Run the algos
    int n = 200;     // max size
    vector<float> p = {0.25,0.5,0.75};   // density
    int nb = 10;     // number of test maximum for each n-size Graph of density p

    //vector<pair<pair<int,float>,vector<Graph>>> VGs = Create_Graphs(n,p,nb);
    //saveVGS(VGs);

    vector<pair<pair<int,float>,vector<Graph>>> VGs = loadGraphs(n, nb, p);
    p = {0.25,0.5,0.75};

    Run_Algos(VGs,28,p,"constructive",10);
    Run_Algos(VGs,28,p,"local_search",10);
    Run_Algos(VGs,28,p,"tabu_search",10);
    // Run_Algos(VGs,26,p,"exact",10);


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