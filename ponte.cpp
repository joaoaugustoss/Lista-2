#include "ponte.h"
#include "utilitario.h"

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
    list<string> arestasCaminhamento = arestas;
    list<string> arestasRemovidas;
    list<string> resultados;
    list<string> resp;
    int sizeArestas = arestas.size();

    for(list<string>::iterator i = arestas.begin(); i != arestas.end(); i++){
        if(!utilitario::contains(arestasRemovidas, *i)){
            
            arestasRemovidas.push_back(*i);
            arestasCaminhamento.remove(*i);

            gCopy.setArestas(arestasCaminhamento);
            gCopy.setSucessores();


            resultados = caminhamento(arestasCaminhamento, vertice);
            //utilitario::printList(resultados);
            //cout << endl;
            arestasCaminhamento = arestas;
            if(resultados.size() != gCopy.getVertices().size()){
                resp.push_back(*i);
                cout << "Aresta removida: " << *i << endl;
                utilitario::printList(resultados);
            }
        }
    }
    

    
    return resp; 
}

list<string> ponte::caminhamento(list<string> arestasCaminhamento, string verticeInicio){
    list<string> bucket;
    list<string> resp;
    list<string> vertices = gCopy.getVertices();
    vector<vector<string>> sucessores = gCopy.getSucessores();
    bool visitados[vertices.size()];

    resp.push_back(verticeInicio);
    bucket.push_back(verticeInicio);
    visitados[utilitario::getIndex(vertices, verticeInicio)] = true;
    while(!bucket.empty()) {
        list<string>::iterator itBucket = bucket.end();
        itBucket--;
        string verticeAtual = *itBucket;
        bucket.pop_back();
        int indice = utilitario::getIndex(vertices, verticeAtual);
        int atualSucSize = sucessores[indice].size();

        for(int i = 0; i < atualSucSize; i++){
            string sucessorAtual = sucessores[indice][i];
            int indiceSucAtual = utilitario::getIndex(vertices, sucessorAtual);
            if(!visitados[indiceSucAtual]){
                visitados[indiceSucAtual] = true;
                bucket.push_back(sucessorAtual);
                resp.push_back(sucessorAtual);
            }

        }
    }
    
    return resp;
}



graph ponte::getGCopy(){
    return this->gCopy;
}




void ponte::tarjan(){
    
}