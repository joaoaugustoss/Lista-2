#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <list>
#include <string>

using namespace std;

class graph{
    private:
        list<string> vertices;
        list<string> arestas;   
        list<string> sucessores;
        list<string> predecessores;

    public:
        graph();
        graph(const graph& rhs) {
            this->vertices = rhs.vertices;
            this->arestas = rhs.arestas;
            this->sucessores = rhs.sucessores;
            this->predecessores = rhs.predecessores;
        }

        void setVertices(list<string>); //ok
        void setArestas(list<string>); //ok
        void setSucessores(); //ok 
        void setPredecessores(); //ok

        list<string> getVertices(); //ok
        list<string> getArestas(); //ok
        list<string> getSucessores(); //ok
        list<string> getPrecessores(); //ok
};


#endif //