#include "graph.h"

graph::graph(){
        
}

list<string> graph::getVertices(){
    return this->vertices;
}
list<string> graph::getArestas(){
    return this->arestas;
}
list<string> graph::getSucessores(){
    return this->sucessores;
}
list<string> graph::getPrecessores(){
    return this->predecessores;
}

void graph::setVertices(list<string> v){
    this->vertices = v;
}

void graph::setArestas(list<string> a){
    this->arestas = a;
}

void graph::setSucessores(list<string> s){
    this->sucessores = s;
}

void graph::setPredecessores(list<string> p){
    this->predecessores = p;
}
