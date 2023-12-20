#include "Testing.h"
#include <iomanip>


vector<pair<pair<int,float>,vector<Graph>>> Create_Graphs(int n, vector<float> p, int nb){
    vector<pair<pair<int,float>,vector<Graph>>> VGs;
    for(int i=2; i<n; i+=2){
        for(int j=0; j<p.size(); j++){
            pair<int,float> np = make_pair(i,p[j]);
            vector<Graph> Vg;
            for(int k=0; k<nb; k++){
                Graph g(i,p[j]);
                Vg.push_back(g);
            }
            VGs.push_back(make_pair(np,Vg));
        }
    }
    return VGs;
}

void Run_Algos(vector<pair<pair<int,float>,vector<Graph>>> VGs, int n, vector<float> p , string algo, int nb){
    if(n%2==1){
        n--;
    }
    for(int i=0; i<p.size(); i++){
        ostringstream stringp;
        stringp << std::fixed << std::setprecision(2) << p[i];
        ofstream filetime;
        string file_time = "../csv/" + algo + "_" + stringp.str() + "_time.csv";
        filetime.open(file_time, ios::trunc);
        ofstream filenbedge;
        string file_nbedge = "../csv/" + algo + "_" + stringp.str() + "_nbedge.csv";
        filenbedge.open(file_nbedge, ios::trunc);
        filetime.close();
        filenbedge.close();
    }

    int l=0;
    vector<pair<int,int>> Exact_Time;
    for(int i=2; i<=n*p.size(); i+=2){
        pair<int,float>np = VGs[l].first;
        vector<Graph> Vg = VGs[l].second;
        ostringstream stringp;
        stringp << std::fixed << std::setprecision(2) << np.second;

        ofstream filetime;
        string file_time = "../csv/" + algo + "_" + stringp.str() + "_time.csv";
        filetime.open(file_time,ios::app);
        ofstream filenbedge;
        string file_nbedge = "../csv/" + algo + "_" + stringp.str() + "_nbedge.csv";
        filenbedge.open(file_nbedge,ios::app);
        int moytime = 0;
        int moynbedge = 0;
        for(int k=0; k<nb; k++){
            cout << algo << " Algorithm :" << endl;
            vector<vector<int>> result;
            auto start = high_resolution_clock::now();
            if(algo=="exact"){
                result = Vg[k].exactAlgorithm();
            }else if(algo=="constructive"){
                result = Vg[k].constructiveHeuristic();
            }else if(algo=="local_search"){
                result = Vg[k].constructiveHeuristic();
                result = Vg[k].localHeuristic(result);
            }else{
                result = Vg[k].metaheuristic(500,200);
            }
            auto stop = high_resolution_clock::now();
            int duration = duration_cast<microseconds>(stop - start).count();
            int nbedges = Vg[k].getNumberOfEdgesLinkingTwoGroups(result[0], result[1]);
            cout << "n: " << Vg[k].getN() << " p: " << np.second << " - nb of edges: " << nbedges << endl;
            cout << "time: " << duration << endl << endl;
            moytime = moytime + duration;
            moynbedge = moynbedge + nbedges;
        }
        moytime = moytime/nb;
        moynbedge = moynbedge/nb;
        cout << endl << "moytime: " << moytime << endl << "moynbedge : " << moynbedge << endl <<  "--------------------"  << endl;
        filetime << np.first << ";" << moytime << endl;
        filetime.close();
        filenbedge << np.first << ";" << moynbedge << endl;
        filenbedge.close();
        l++;
    }
}

void Test_With_Instance(string instancepath,string algo){
    ifstream inputFile(instancepath);
    if (!inputFile.is_open()) {
        return;
    }
    string line;
    getline(inputFile, line);
    istringstream iss(line);
    int n, m;
    iss >> n >> m;
    Graph g(n);

    getline(inputFile, line);
    istringstream iss2(line);
    int u, v;
    while (iss2 >> u >> v) {
        g.addEdge(u,v);
        iss2.ignore(2, ' ');
    }
    inputFile.close();

    g.writeSolutions(instancepath,algo);
}
