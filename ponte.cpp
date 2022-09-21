#include "ponte.h"

ponte::ponte(graph g){
    this->g = g;
    graph copy(g);
    this->gCopy = copy;
}

list<string> ponte::bruteForce(){
    // recebe um vértice qualquer OK
    // recebe lista de arestas OK
    // remove uma aresta
    // caminha
        //  Se lista de vértices percorridos == lista de vértices de G 
            // Aresta não é ponte
        // Contrário 
            // Aresta é ponte

    string vertice = gCopy.getVertices().front();
    list<string> arestas = gCopy.getArestas();


    list<string> foo;
    return foo; 
}


graph ponte::getGCopy(){
    return this->gCopy;
}




void ponte::tarjan(){
    
}