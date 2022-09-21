#include "graph.h"

graph::graph(){
        
}

list<string> graph::getVertices(){
    return this->vertices;
}
list<string> graph::getArestas(){
    return this->arestas;
}
list<string>* graph::getSucessores(){
    return this->sucessores;
}
list<string>* graph::getPrecessores(){
    return this->predecessores;
}

void graph::setVertices(list<string> v){
    this->vertices = v;
}

void graph::setArestas(list<string> a){
    this->arestas = a;
}

void graph::setSucessores(){
    
    list<string>::iterator itVertices = vertices.begin();
    list<string>::iterator itArestas;

    list<string> aux[vertices.size()];
    sucessores = aux;

    for(itArestas = arestas.begin(); itArestas != arestas.end(); itArestas++){
        string aresta = *itArestas; 
        // AB
        string verticeEsquerda;
        string verticeDireita;
        verticeEsquerda.push_back(aresta.at(0));
        verticeDireita.push_back(aresta.at(1));
        // Garantindo que não haja arestas com vértices iguais (looping)
        if(verticeEsquerda.compare(verticeDireita)) {
            int indiceVertice = getIndex(vertices, verticeEsquerda);
            
            
            bool encontrado = find(sucessores[indiceVertice].begin(), sucessores[indiceVertice].end(), verticeDireita) != sucessores[indiceVertice].end();
            
            // arestas 
            // ab (a) -> indice em vertices
            // sucessores[indice].add(b)

            //cout << encontrado << endl;
            if(!encontrado) {
                sucessores[indiceVertice].push_back(verticeDireita);
            }
        }
    }
}


int graph::getIndex(list<string> lista, string a) {
    int i = 0;
    list<string>::iterator it = lista.begin();
    for(it = lista.begin(); it != lista.end(); it++, i++){
        string content = *it;
        if(a.compare(content) == 0 ) {
            it = lista.end(); 
            it--;

        }
    }
    return --i;
}

void graph::setPredecessores(){
    
}
