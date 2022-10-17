#include "ponte.h"
#include "utilitario.h"

ponte::ponte(graph g)
{
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
vector<vector<string>> ponte::bruteForce()
{
    
    //graph copy(this->g);
    //this->gCopy = copy;
    // Utilizando uma cópia do grafo, para evitar problemas
    string vertice = gCopy.getVertices().front();
    list<string> arestas = gCopy.getArestas();
    // Lista auxiliar de arestas
    list<string> arestasCaminhamento = arestas;
    list<string> arestasRemovidas;
    vector<string> resultados;
    vector<vector<string>> resp;
    int sizeArestas = arestas.size();

    // Iterando por todas as arestas com o intuito de removê-las uma por uma e testar quais são pontes
    for (list<string>::iterator i = arestas.begin(); i != arestas.end(); i++)
    {
        string content = *i;
        // Controle para evitar remoção de arestas repetidas (Talvez não seja necessário)
        if (!utilitario::contains(arestasRemovidas, content))
        {
            string reversed(content);
            reverse(reversed.begin(), reversed.end());

            arestasRemovidas.push_back(content);
            arestasRemovidas.push_back(reversed);
            arestasCaminhamento.remove(content);
            arestasCaminhamento.remove(reversed);

            // Setando no GrafoCopia a nova lista de arestas, e gerando a nova lista de sucessores
            gCopy.setArestas(arestasCaminhamento);
            gCopy.setSucessores();

            resultados = caminhamento(vertice);
            arestasCaminhamento = arestas;
            // Caso a quantidade de vértices caminhados seja diferente (inferior) da quantidade de vértices do grafo,
            // encontramos uma ponte
            if (resultados.size() != gCopy.getVertices().size())
            {
                vector<string> element;
                element.push_back(content);
                resp.push_back(element);
            } // Fim verificação de ponte

        } // Fim verificação contains arestas

    } // Fim iterator arestas


    return resp;
}

/*
    Método que fará o caminhamento em profundidade utilizando listas.

    A estratégia é:
        Adicionar o vértice inicial em uma lista "bucket"
        Enquanto "bucket" não vazio:
            Remover esse vértice inicial, e adicionar seu sucessores em bucket (caso já não tenham sido adicionados)
            Atualizar valor de vértice atual para seu primeiro sucessor

*/
vector<string> ponte::caminhamento(string verticeInicio)
{
    // Declaração de variáveis auxiliares
    list<string> bucket;
    vector<string> resp;
    list<string> vertices = gCopy.getVertices();
    vector<vector<string>> sucessores = gCopy.getSucessores();
    bool visitados[vertices.size()];

    // Adicionando vértice inicial às listas auxiliares
    resp.push_back(verticeInicio);
    bucket.push_back(verticeInicio);
    // Setando-o como visitado
    visitados[utilitario::getIndex(vertices, verticeInicio)] = true;

    while (!bucket.empty())
    {
        // Remoção do vértice na última posição da lista
        list<string>::iterator itBucket = bucket.end();
        itBucket--;
        string verticeAtual = *itBucket;
        bucket.pop_back();

        int indice = utilitario::getIndex(vertices, verticeAtual);
        int atualSucSize = sucessores[indice].size();

        // Iteração para adicionar às listas auxiliares os sucessores não visitados
        for (int i = 0; i < atualSucSize; i++)
        {
            string sucessorAtual = sucessores[indice][i];
            int indiceSucAtual = utilitario::getIndex(vertices, sucessorAtual);
            if (!visitados[indiceSucAtual])
            {
                visitados[indiceSucAtual] = true;
                bucket.push_back(sucessorAtual);
                resp.push_back(sucessorAtual);
            } // Fim verificação de visitados
        }     // Fim iteração sucessores
    }         // Fim iteração bucket

    // Retorno da lista de vértices visitados
    return resp;
}

/*
    Método que fará a verificação de arestas que são pontes no grafo através do algoritmo TARJAN.
    O algoritmo implementado do TARJAN segue a ideia apresentada no vídeo:
    https://www.youtube.com/watch?v=hKhLj7bfDKk&ab_channel=WilliamFiset
    com uma pequena alteração para encontrarmos as pontes.

    O conceito principal do algoritmo TARJAN é encontrar os componentes fortemente conexos, ou seja, componentes que fecham ciclos.
    Uma ponte é uma aresta que não faz parte de um ciclo.
    Portanto, ao encontrarmos todos os componentes fortemente conexos, todas as arestas que não fizerem parte desses componentes
    são arestas pontes.
    A maneira como está implementada, todas as verificações necessárias são feitas no momento do caminhamento (DFS)

    Teremos 5 estruturas auxiliares:
        - "id" -> ID do vértice atual
        - vetor "low" -> Representando o menor ID existente do componente (menor id = id do vértice que começou o ciclo)
                        - Importante para setar qual componente o vértice faz parte
        - vetor "ids" -> Um vetor que indica se o vértice já foi visitado (seu conteúdo será o ID do vértice)
        - stack "pilha" -> Uma pilha para manter controle de todos os vértices do componente atual
        - vetor "onStack" -> Um vetor para manter controle dos vértices que estão na pilha

    O algoritmo funcionará da seguinte maneira:
        - Aplicaremos o DFS
        - Setaremos em "ids" e "low" o ID do vértice atual, colocaremos na stack e acessaremos seus sucessores
            - Caso sucessor não tenha sido visitado:
                Iniciaremos uma nova recusão
            - Caso sucessor seja diferente de seu antecessor (evitando loop) e sucessor já está na pilha:
                Setaremos "low" como sendo o menor "ID" entre seu próprio "ID" e de seu antecessor
                (Estamos "colocando" sucessor no mesmo componente que seu antecessor)
            *- Caso valor em "low" do sucessor seja maior que "ID" de seu antecessor:
                Adicionaremos aresta à lista de resposta
                (Achamos uma ponte)*
        Por final, Caso "ID" do atual seja igual a "low" do atual:
            Desempilharemos todos elementos da stack que fazem parte do mesmo componente
            (Chegamos ao fim do componente)

*/

vector<vector<string>> ponte::tarjan()
{
    // Declaração de variáveis auxiliáres
    gCopy.setSucessores();
    list<string> arestas = gCopy.getArestas();

    int size = gCopy.getVertices().size();
    int qnt = 0;
    id = 0;

    // Populando vetores com valores padrões
    respTarjan.resize(arestas.size());
    for (int i = 0; i < respTarjan.size(); i++)
    {
        respTarjan[i].clear();
    }
    low.resize(size);
    ids.resize(size);
    naPilha.resize(size);
    for (int i = 0; i < size; i++)
    {
        ids[i] = -1;
        low[i] = 0;
        naPilha[i] = false;
    }

    vector<vector<string>> adj = gCopy.getSucessores();
    // Iteração que passará por cada vértice para verificar os componentes (Caso não tenham sido visitados)
    for (int i = 0; i < size; i++)
    {
        if (ids[i] == -1)
        {
            list<string> vertices = gCopy.getVertices();
            list<string>::iterator it = vertices.begin();
            advance(it, i);
            string atual = *it;
            qnt = DFsearch(atual, " ");
        } // Fim verificação visitado
    }     // Fim iteração vértices
    respTarjan.resize(qnt);
    return this->respTarjan;
}

/*
    Método que fará DFS no grafo.
    Foi alterado para se encaixar na ideia do TARJAN
*/
int ponte::DFsearch(string atual, string anterior)
{
    // Passo inicial
    int i = 0;
    pilha.push(atual);
    int indiceAtual = utilitario::getIndex(gCopy.getVertices(), atual);
    naPilha[indiceAtual] = true;
    ids[indiceAtual] = low[indiceAtual] = id++;

    vector<string> suc = gCopy.getSucessores()[indiceAtual];

    // Iterando pelos sucessores do vértice atual
    for (string sucessor : suc)
    {
        int indiceSuc = utilitario::getIndex(gCopy.getVertices(), sucessor);

        if (ids[indiceSuc] == -1)
        {
            i = DFsearch(sucessor, atual);
        } // Fim verificação visitado

        if ((sucessor.compare(anterior) != 0) && naPilha[indiceSuc])
        {
            low[indiceAtual] = min(low[indiceAtual], low[indiceSuc]);
        } // Fim verificação de mínimo

        if (low[indiceSuc] > ids[indiceAtual])
        {
            string aresta = atual + sucessor + "\0";
            respTarjan[i++].push_back(aresta);
        } // Fim verificação ponte
    }     // Fim iteração sucessores

    // Quando achar um elemento que seu ID é igual ao valor que está na lista de LOW
    // Significa que achamos um componente fortemente conexo
    // (nesse caso, podemos falar que achamos o elemento que "iniciou" o componente)
    // Então devemos remover todos os vértices que possuem o mesmo valor de LOW e que estão na pilha
    if (ids[indiceAtual] == low[indiceAtual])
    {
        for (string node = pilha.top();; node = pilha.top())
        {
            int indiceNode = utilitario::getIndex(gCopy.getVertices(), node);
            pilha.pop();
            naPilha[indiceNode] = false;
            low[indiceNode] = ids[indiceNode];
            // Garantindo que não remova elementos que possam estar na pilha
            // mas que não fazem parte do componente
            if (node.compare(atual) == 0)
                break;
        } // Fim desempilhamento
    }     // Fim verificação para desempilhamento
    return i;
}

graph ponte::getGCopy()
{
    return this->gCopy;
}

vector<string> ponte::oddVertices()
{
    vector<vector<string>> aux = g.getSucessores();
    vector<string> resp;
    vector<vector<string>>::iterator row;
    int index = 0;

    for (row = aux.begin(); row != aux.end(); row++, index++)
    {

        if (row->size() % 2 != 0)
        {
            list<string> content = g.getVertices();
            list<string>::iterator it = content.begin();
            advance(it, index);
            resp.push_back(*it);
        }
    }

    return resp;
}

bool ponte::isEulerian()
{
    bool resp = false;
    int qnt = oddVertices().size();

    if (qnt == 0 || qnt == 2)
        resp = true;

    return resp;
}

/*
    Função para retornar o caminho euleriano presente no grafo
    Dividido em etapas:
        1- encontrar o vértice para começar (grau ímpar, verificar se é vértice de ponte ou não)
                                            (Se não houver, grau par qualquer)
        2- Após encontrar vértice para começar, caminharemos por seus sucessores seguindo os requisitos:
            - Caso exista aresta que não é ponte, iremos priorizar ela
            - Caso não existe aresta não ponte, iremos escolher ela
        3- Adicionaremos vértice caminhado ao bucket (será o próximo vértice percorrido)
        4- Adicionaremos vértice caminhado à resp 
        5- Repete o passo a passo acima, até o momento em que não teremos mais vértices para caminhar
*/
vector<string> ponte::fleuryTarj()
{
    /*
        Se oddVert vazio (Ciclo euleriano)
            Escolhe primeiro vértice em Vert
        else (Caminho euleriano)
            Escolhe primeiro vértice em oddVert

        adicionar vertice à resp

        (Contexto igual à DFS)
        Adiciona vertice ao bucket
        Enquanto bucket não vazio
            foo := remove bucket
            Se foo possui aresta não contida em PONTE
                Caminha para aresta
                remove aresta (gCopy)
            Senão
                Caminha para aresta
                remove aresta (gCopy)

            re-calcula Ponte (tarjan)

            visitado[vertice incidido] = true
            adiciona vertice incidido à resp e à bucket

    */
   clock_t start, end;
   start = clock();
    vector<string> resp;
    vector<string> bucket;
    if (!isEulerian())
        return resp;
    string inicial;
    vector<string> oddVert = oddVertices();
    vector<vector<string>> sucessores = gCopy.getSucessores();
    list<string> vertices = gCopy.getVertices();
    bool terminou = false;

    if (oddVert.empty())
    {
        inicial = *gCopy.getVertices().begin();
    }
    else
    {
        inicial = oddVert[0];
    }

    bucket.push_back(inicial);
    int count = 0;
    while (!bucket.empty())
    {
        string caminhe = "";
        terminou = false;
        vector<string>::iterator it = bucket.end();
        it--;
        string removed = *it;
        bucket.pop_back();

        if (gCopy.getArestas().size() > 0)
        {
            vector<vector<string>> ponte = this->tarjan();
            int pntSize = ponte.size();
           
            list<string> ar = gCopy.getArestas();

            int indice = utilitario::getIndex(vertices, removed);
            vector<string> removedSuc = sucessores[indice];

            // Ideia será iterar por todos os sucessores de "REMOVED"
            // e ver se algum NÃO é ponte, se NÃO FOR PONTE, escolheremos ele para caminhar
            // Caso só tenha ponte, ecolheremos o último verificado
            vector<string>::iterator remIt = removedSuc.begin();
            while (!terminou)
            {
                int ammount = 0;
                // Itera por todos os sucessores de REMOVED
                // String testagem = removed + sucessor
                // Se testagem não está contido em respTarjan
                //      Pare looping, caminha para *it

                string testagem = removed + *remIt;

                vector<vector<string>>::iterator row = ponte.begin();
                vector<vector<string>>::iterator stopper = ponte.end();
                // stopper--;

                for (; row != stopper; row++)
                {
                    if ((!utilitario::contains(*row, testagem)) && (utilitario::contains(ar, testagem)))
                    {
                        // Terminando o looping externo
                        terminou = true;

                        // Salvando qual o vértice devemos caminhar
                        caminhe = *remIt;

                        // Terminando o looping interno
                        row = stopper;
                        row--;
                    }

                }

                //  Caso não encontre arestas NÃO PONTES,
                if (remIt == removedSuc.end())
                {
                    terminou = true;
                    remIt--;
                    caminhe = *remIt; // Aresta verificada
                }
                remIt++;
            }
            list<string> arestas = gCopy.getArestas();


            arestas.remove(removed + caminhe);
            arestas.remove(caminhe + removed);

            gCopy.setArestas(arestas);

            bucket.push_back(caminhe);

        }
        resp.push_back(removed);
    }
    end = clock();
    double time_taken = double(end - start) / double(CLOCKS_PER_SEC);
    cout << "Time taken by Fleury Tarjan: " << time_taken << " sec " << endl;

    return resp;
}

/*
    Função para retornar o caminho euleriano presente no grafo
    Dividido em etapas:
        1- encontrar o vértice para começar (grau ímpar, verificar se é vértice de ponte ou não)
                                            (Se não houver, grau par qualquer)
        2- Após encontrar vértice para começar, caminharemos por seus sucessores seguindo os requisitos:
            - Caso exista aresta que não é ponte, iremos priorizar ela
            - Caso não existe aresta não ponte, iremos escolher ela
        3- Adicionaremos vértice caminhado ao bucket (será o próximo vértice percorrido)
        4- Adicionaremos vértice caminhado à resp 
        5- Repete o passo a passo acima, até o momento em que não teremos mais vértices para caminhar
*/
vector<string> ponte::fleuryBruteF()
{
    clock_t start, end;
    start = clock();
    graph copy(this->g);
    graph gCopyP = copy;
    /*
        Se oddVert vazio (Ciclo euleriano)
            Escolhe primeiro vértice em Vert
        else (Caminho euleriano)
            Escolhe primeiro vértice em oddVert

        adicionar vertice à resp

        (Contexto igual à DFS)
        Adiciona vertice ao bucket
        Enquanto bucket não vazio
            foo := remove bucket
            Se foo possui aresta não contida em PONTE
                Caminha para aresta
                remove aresta (gCopyP)
            Senão
                Caminha para aresta
                remove aresta (gCopyP)

            re-calcula Ponte (tarjan)

            visitado[vertice incidido] = true
            adiciona vertice incidido à resp e à bucket

    */
    vector<string> resp;
    vector<string> bucket;
    if (!isEulerian())
        return resp;
    string inicial;
    vector<string> oddVert = oddVertices();
    vector<vector<string>> sucessores = gCopyP.getSucessores();
    list<string> vertices = gCopyP.getVertices();
    bool terminou = false;

    if (oddVert.empty())
    {
        inicial = *gCopyP.getVertices().begin();
    }
    else
    {
        inicial = oddVert[0];
    }

    bucket.push_back(inicial);
    int count = 0;
    while (!bucket.empty())
    {
        string caminhe = "";
        terminou = false;
        vector<string>::iterator it = bucket.end();
        it--;
        string removed = *it;
        bucket.pop_back();

        if (gCopyP.getArestas().size() > 0)
        {
            vector<vector<string>> ponte = this->bruteForce();

            int pntSize = ponte.size();
           
            list<string> ar = gCopyP.getArestas();

            int indice = utilitario::getIndex(vertices, removed);
            vector<string> removedSuc = sucessores[indice];

            // Ideia será iterar por todos os sucessores de "REMOVED"
            // e ver se algum NÃO é ponte, se NÃO FOR PONTE, escolheremos ele para caminhar
            // Caso só tenha ponte, ecolheremos o último verificado
            vector<string>::iterator remIt = removedSuc.begin();
            while (!terminou)
            {
                int ammount = 0;
                // Itera por todos os sucessores de REMOVED
                // String testagem = removed + sucessor
                // Se testagem não está contido em respTarjan
                //      Pare looping, caminha para *it

                string testagem = removed + *remIt;

                vector<vector<string>>::iterator row = ponte.begin();
                vector<vector<string>>::iterator stopper = ponte.end();
                // stopper--;

                for (; row != stopper; row++)
                {
                    if ((!utilitario::contains(*row, testagem)) && (utilitario::contains(ar, testagem)))
                    {
                        // Terminando o looping externo
                        terminou = true;

                        // Salvando qual o vértice devemos caminhar
                        caminhe = *remIt;

                        // Terminando o looping interno
                        row = stopper;
                        row--;
                    }

                }

                //  Caso não encontre arestas NÃO PONTES,
                if (remIt == removedSuc.end())
                {
                    terminou = true;
                    remIt--;
                    caminhe = *remIt; // Aresta verificada
                }
                remIt++;
            }
            list<string> arestas = gCopyP.getArestas();

            arestas.remove(removed + caminhe);
            arestas.remove(caminhe + removed);

            gCopyP.setArestas(arestas);

            bucket.push_back(caminhe);

        }
        resp.push_back(removed);
    }

    end = clock();
    double time_taken = double(end - start) / double(CLOCKS_PER_SEC);
    cout << "Time taken by Fleury Naive: " << time_taken << " sec " << endl;

    return resp;
}