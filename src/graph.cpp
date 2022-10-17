#include "graph.h"
#include "utilitario.h"
#include <stdlib.h>
#include <algorithm>

graph::graph(){
        
}

list<string> graph::getVertices(){
    return this->vertices;
}
list<string> graph::getArestas(){
    return this->arestas;
}
vector<vector<string> > graph::getSucessores(){
    return this->sucessores;
}
vector<vector<string> > graph::getPredecessores(){
    return this->predecessores;
}

void graph::setVertices(list<string> v){
    this->vertices = v;
}

void graph::setArestas(list<string> a){
    this->arestas = a;
}

void graph::setSucessores(){
    // Instanciando iterador da lista de vértices
    list<string>::iterator itVertices = vertices.begin();
    list<string>::iterator itArestas;
    int size = vertices.size();

    // Vetor auxiliar que conterá os vetores de sucessores de cada vértice
    vector<vector<string> > aux;

    // Dando resize para que fique do tamanho necessário
    aux.resize(size);

    // Iterando por todas as arestas existentes e verificando os vértices contidos nas arestas
    // Adicionando ao vetor de sucessores do "verticeEsquerda" o verticeDireita (caso não exista ainda)
    for(itArestas = arestas.begin(); itArestas != arestas.end(); itArestas++){
        string aresta = *itArestas; 
        // AB
        string verticeEsquerda; 
        string verticeDireita;
        verticeEsquerda.push_back(aresta.at(0)); // A
        verticeDireita.push_back(aresta.at(1)); // B
        // Garantindo que não haja arestas com vértices iguais (looping)
        if(verticeEsquerda.compare(verticeDireita)) {
            // Pegando o índice do vértice 
            int indiceVertice = utilitario::getIndex(vertices, verticeEsquerda);
            
            // Verificando se o mesmo já existe no vetor
            bool encontrado = utilitario::contains(aux[indiceVertice], verticeDireita);
            
            if(!encontrado) {
                aux[indiceVertice].push_back(verticeDireita);
            }
            
        }

        // Mesmo conceito da verificação acima, está sendo feito para garantir que o grafo seja não-direcional
        if(verticeDireita.compare(verticeEsquerda)) {
            int indiceVertice = utilitario::getIndex(vertices, verticeDireita);
            
            
            bool encontrado = utilitario::contains(aux[indiceVertice], verticeEsquerda);
            
            if(!encontrado) {
                aux[indiceVertice].push_back(verticeEsquerda);
            }
            
        }
    }
    
    

    for(int i = 0; i < size; i++){
        sort(aux[i].begin(), aux[i].end());
    }
    this->sucessores = aux;
}






void graph::setPredecessores(){
     // Instanciando iterador da lista de vértices
    list<string>::iterator itVertices = vertices.begin();

    list<string>::iterator itArestas;
    int size = vertices.size();
    
    // Vetor auxiliar que conterá os vetores de predecessores de cada vértice
    vector<vector<string> > aux;
    
    // Dando resize para que fique do tamanho necessário
    aux.resize(size);

    // Iterando por todas as arestas existentes e verificando os vértices contidos nas arestas
    // Adicionando ao vetor de precessores do "verticeDireita" o verticeEsquerda (caso não exista ainda)
    for(itArestas = arestas.begin(); itArestas != arestas.end(); itArestas++){
        string aresta = *itArestas; 
        // AB
        string verticeEsquerda; 
        string verticeDireita;
        verticeEsquerda.push_back(aresta.at(0)); // A
        verticeDireita.push_back(aresta.at(1)); // B
        // Garantindo que não haja arestas com vértices iguais (looping)
        if(verticeDireita.compare(verticeEsquerda)) {
            int indiceVertice = utilitario::getIndex(vertices, verticeDireita);
            
            
            bool encontrado = utilitario::contains(aux[indiceVertice], verticeEsquerda);
            
            if(!encontrado) {
                aux[indiceVertice].push_back(verticeEsquerda);
            }
            
        }
        // Mesmo conceito da verificação acima, está sendo feito para garantir que o grafo seja não-direcional
        if(verticeEsquerda.compare(verticeDireita)) {
            // Pegando o índice do vértice 
            int indiceVertice = utilitario::getIndex(vertices, verticeEsquerda);
            
            // Verificando se o mesmo já existe no vetor
            bool encontrado = utilitario::contains(aux[indiceVertice], verticeDireita);
            
            if(!encontrado) {
                aux[indiceVertice].push_back(verticeDireita);
            }
            
        }

    }
    for(int i = 0; i < size; i++)
        sort(aux[i].begin(), aux[i].end());
    this->predecessores = aux;

}
