#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <list>
#include <vector>
#include <string>

using namespace std;

class graph{
    private:
        list<string> vertices;
        list<string> arestas;   
        vector<vector<string>> sucessores;
        vector<vector<string>> predecessores;

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
        vector<vector<string>> getSucessores(); //ok
        vector<vector<string>> getPredecessores(); //ok

        //int getIndex(list<string>, string);
};


#endif //