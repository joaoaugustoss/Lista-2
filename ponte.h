#ifndef PONTE_H
#define PONTE_H

#include "graph.h"
#include <stack> 


class ponte {
    private:
        // Global attributes
        graph g;
        graph gCopy;

        // Tarjan attributes
        vector<vector<string>> respTarjan;
        stack<string> pilha;
        vector<bool> naPilha;
        vector<int> ids;
        vector<int> low;
        int id;

        vector<string> caminhamento(string);
        int DFsearch(string, string);
    
    public:
        ponte(graph);
        vector<vector<string>> bruteForce();
        vector<vector<string>> tarjan();
        vector<string> fleuryTarj();
        vector<string> fleuryBruteF();
        graph getGCopy();
        bool isEulerian();
        vector<string> oddVertices();


};

#endif // PONTE_H