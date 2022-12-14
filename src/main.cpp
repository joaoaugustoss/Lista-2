#include <iostream>

#include "ponte.h"
#include "utilitario.h"

using namespace std;

int main(){
    clock_t start, end;
    start = clock();
    graph g;
    list<string> foo;
    foo.push_back("a");
    foo.push_back("b");
    foo.push_back("c");
    foo.push_back("d");
    foo.push_back("e");
    g.setVertices(foo);
    foo.clear();
    foo.push_back("ab");
    foo.push_back("ba");
    foo.push_back("bc");
    foo.push_back("cb");
    foo.push_back("ac");
    foo.push_back("ca");
    foo.push_back("cd");
    foo.push_back("dc");
    foo.push_back("de");
    foo.push_back("ed");
    g.setArestas(foo);
    g.setSucessores();
    g.setPredecessores();
    ponte pn = ponte(g);
    ponte ptj = ponte(g);

    list<string> vertices = g.getVertices();

    cout << "Sucessores: " << endl;
    int size = vertices.size(); 
    vector<vector<string> > barz = g.getSucessores();
    for(int i = 0; i < size; i++){
        utilitario::printList(barz[i]);
    }
    
    vector<vector<string>> pontes = pn.bruteForce();
    cout << "Todas as pontes encontradas (BF): " << pontes.size() << endl;
    for(vector<vector<string>>::iterator it = pontes.begin(); it != pontes.end(); it++){

        if( !it->empty()){
            utilitario::printList(*it);
        }
    }
    ponte pbf = ponte(g);
    vector<string> fleuryBF = pbf.fleuryBruteF();
    cout << "Fleury length: " << fleuryBF.size() << endl;
    cout << "Eulerian path: ";
    utilitario::printList(fleuryBF);

    vector<vector<string>> componentes = ptj.tarjan();
    cout << "Todas as pontes encontradas (Tarjan): " << componentes.size() << endl;
    for(vector<vector<string>>::iterator it = componentes.begin(); it != componentes.end(); it++){
        if( !it->empty()){
            utilitario::printList(*it);
        }
    }
    vector<string> fleuryT = ptj.fleuryTarj();
    cout << "Fleury length: " << fleuryT.size() << endl;
    cout << "Eulerian path: ";
    utilitario::printList(fleuryT);

    end = clock();
    double time_taken = double(end - start) / double(CLOCKS_PER_SEC);
    cout << "Time taken by main: " << time_taken << " sec " << endl;

    return 0;
}