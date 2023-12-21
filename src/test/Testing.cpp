#include "Testing.h"

vector<pair<pair<int,float>,vector<Graph>>> Create_Graphs(int n, vector<float> p, int nb){
    vector<pair<pair<int,float>,vector<Graph>>> VGs;
    for(int i=2; i<=n; i+=2){
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

void Run_Algos(vector<pair<pair<int,float>,vector<Graph>>> &VGs, int n, vector<float> p , string algo, int nb){
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
                result = exactAlgorithm(Vg[k]);
            }else if(algo=="constructive"){
                result = constructiveHeuristic(Vg[k]);
            }else if(algo=="local_search"){
                result = constructiveHeuristic(Vg[k]);
                result = localHeuristic(Vg[k], result);
            }else{
                result = metaheuristic(Vg[k], 100,20);
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

void writeSolutions(Graph &G, string instancepath, string algo){
    instancepath.pop_back();
    instancepath.pop_back();
    instancepath.pop_back();
    ofstream file;
    vector<vector<int>> result;
    if(algo=="exact"){
        string file_name = instancepath + "_exact.out";
        file.open(file_name);
        result = exactAlgorithm(G);
    }else if(algo=="constructive"){
        string file_name = instancepath + "_constructive.out";
        file.open(file_name);
        result = constructiveHeuristic(G);
    }else if(algo=="exact"){
        string file_name = instancepath + "_local_search.out";
        file.open(file_name);
        result = constructiveHeuristic(G);
        result = localHeuristic(G, result);
    }else {
        string file_name = instancepath + "_tabu_search.out";
        file.open(file_name);
        result = metaheuristic(G, 100, 20);
    }

    int nbedges = G.getNumberOfEdgesLinkingTwoGroups(result[0], result[1]);
    file << G.n << " " << nbedges << endl;
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

void Test_With_Instance(string instancepath,string algo){
    instancepath = "../instances/" + algo + "/" + instancepath;
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

    writeSolutions(g, instancepath,algo);
}

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
