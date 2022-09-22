#include "ponte.h"
#include "utilitario.h"

ponte::ponte(graph g){
    this->g = g;
    graph copy(g);
    this->gCopy = copy;
}

/*
    Método que fará a verificação de arestas que são pontes no grafo através da força bruta.
    O conceito é remover uma aresta e caminhar pelo grafo (usando a lista de sucessores),
    caso não seja possível percorrer por todos os vértices, ou seja, tenha criado novos componentes,
    essa aresta é uma ponte.

    A estratégia adotada foi:
    1- Receber um vértice qualquer para iniciar o caminhamento 
    (Devemos lembrar que em um grafo conexo o vértice inicial de busca é indiferente)
    2- Receber a lista de arestas
    3- Remover uma aresta qualquer (não repetida)
    4- Caminhar no grafo com a nova lista de arestas obtida
       No final do caminhamento
       Se lista de vértices percorridos == lista de vértices do grafo
            Aresta não é ponte (não houve criação de novo componente)
       Senão
            Aresta é ponte
*/
list<string> ponte::bruteForce(){
    // Utilizando uma cópia do grafo, para evitar problemas
    string vertice = gCopy.getVertices().front();
    list<string> arestas = gCopy.getArestas();
    // Lista auxiliar de arestas 
    list<string> arestasCaminhamento = arestas;
    list<string> arestasRemovidas;
    list<string> resultados;
    list<string> resp;
    int sizeArestas = arestas.size();

    // Iterando por todas as arestas com o intuito de removê-las uma por uma e testar quais são pontes
    for(list<string>::iterator i = arestas.begin(); i != arestas.end(); i++){
        // Controle para evitar remoção de arestas repetidas (Talvez não seja necessário)
        if(!utilitario::contains(arestasRemovidas, *i)){
            
            arestasRemovidas.push_back(*i);
            arestasCaminhamento.remove(*i);

            // Setando no GrafoCopia a nova lista de arestas, e gerando a nova lista de sucessores
            gCopy.setArestas(arestasCaminhamento);
            gCopy.setSucessores();


            resultados = caminhamento(vertice);
            arestasCaminhamento = arestas;
            // Caso a quantidade de vértices caminhados seja diferente (inferior) da quantidade de vértices do grafo,
            // encontramos uma ponte
            if(resultados.size() != gCopy.getVertices().size()){
                resp.push_back(*i);
                cout << "Aresta removida: " << *i << endl;
                utilitario::printList(resultados);
            } // Fim verificação de ponte

        } // Fim verificação contains arestas

    } // Fim iterator arestas
       
    return resp; 
}

/*
    Método que fará o caminhamento em profundidade utilizando listas para inserir os vértices
    e listas dos sucessores dos vértices

    A estratégia

*/
list<string> ponte::caminhamento(string verticeInicio){
    list<string> bucket;
    list<string> resp;
    list<string> vertices = gCopy.getVertices();
    vector<vector<string> > sucessores = gCopy.getSucessores();
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





vector<string> ponte::tarjan(){
    list<string> arestas = gCopy.getArestas();
    respTarjan.resize(arestas.size());

    int size = gCopy.getVertices().size();
    id = 0;

    low.resize(size, 0);
    ids.resize(size, -1);
    naPilha.resize(size, false);

    vector<vector<string> > adj = gCopy.getSucessores();
    for(int i = 0; i < size; i++){
        if(ids[i] == -1){
            list<string> vertices = gCopy.getVertices();
            list<string>::iterator it = vertices.begin();
            advance(it, i);
            string atual = *it;
            DFsearch(atual, " ");
        }
    }

    return this->respTarjan;
}

void ponte::DFsearch(string atual, string anterior){
    pilha.push(atual);
    int indiceAtual = utilitario::getIndex(gCopy.getVertices(), atual);
    naPilha[indiceAtual] = true;

    ids[indiceAtual] = low[indiceAtual] = id++;

    vector<string> suc = gCopy.getSucessores()[indiceAtual];

    for(string sucessor : suc){
        int indiceSuc = utilitario::getIndex(gCopy.getVertices(), sucessor);

        if(ids[indiceSuc] == -1){
            DFsearch(sucessor, atual);
        }
        if((sucessor.compare(anterior) != 0) && naPilha[indiceSuc]) {
            low[indiceAtual] = min(low[indiceAtual], low[indiceSuc]);
        }
        if(low[indiceSuc] > ids[indiceAtual]){
            string aresta = atual + sucessor;
            respTarjan.push_back(aresta);
        }
    }
    if(ids[indiceAtual] == low[indiceAtual]){
        for(string node = pilha.top();; node = pilha.top()){
            int indiceNode = utilitario::getIndex(gCopy.getVertices(), node);
            pilha.pop();
            naPilha[indiceNode] = false;
            low[indiceNode] = ids[indiceNode];
            if(node.compare(atual) == 0) break;
        }
    }

}


graph ponte::getGCopy(){
    return this->gCopy;
}

