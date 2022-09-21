#ifndef PONTE_H
#define PONTE_H

#include "graph.h"


class ponte {
    private:
        graph g;
        graph gCopy;


    
    public:
        ponte(graph);
        list<string> bruteForce();
        void tarjan();

        graph getGCopy();
};

#endif // PONTE_H