#ifndef PONTE_H
#define PONTE_H

#include "graph.h"
#include <stack> 


class ponte {
    private:
        graph g;
        graph gCopy;

        // Tarjan attributes
        vector<string> respTarjan;
        stack<string> pilha;
        vector<bool> naPilha;
        vector<int> ids;
        vector<int> low;
        int id;

        list<string> caminhamento(string);
        void DFsearch(string, string);
    
    public:
        ponte(graph);
        list<string> bruteForce();
        vector<string> tarjan();

        graph getGCopy();
};

#endif // PONTE_H