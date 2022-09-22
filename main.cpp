#include <iostream>

#include "ponte.h"
#include "utilitario.h"

using namespace std;

int main(){
    graph g;
    list<string> foo;
    /*foo.push_back("a");
    foo.push_back("b");
    foo.push_back("c");
    foo.push_back("d");
    foo.push_back("e");
    foo.push_back("f");
    foo.push_back("g");
    foo.push_back("h");
    foo.push_back("i");
    g.setVertices(foo);
    foo.clear();
    foo.push_back("ab");
    foo.push_back("ad");
    foo.push_back("ae");
    foo.push_back("bc");
    foo.push_back("bd");
    foo.push_back("be");
    foo.push_back("cd");
    foo.push_back("ce");
    foo.push_back("cf");
    foo.push_back("df");
    foo.push_back("ef");
    foo.push_back("fg");
    foo.push_back("gh");
    foo.push_back("gi");
    foo.push_back("hi");*/
    foo.push_back("a");
    foo.push_back("b");
    foo.push_back("c");
    foo.push_back("d");
    foo.push_back("e");
    g.setVertices(foo);
    foo.clear();
    foo.push_back("ab");
    foo.push_back("bc");
    foo.push_back("ca");
    foo.push_back("cd");
    foo.push_back("de");
    g.setArestas(foo);
    g.setSucessores();
    g.setPredecessores();
    ponte pn = ponte(g);

    list<string> vertices = g.getVertices();

    cout << "Sucessores: " << endl;
    int size = vertices.size(); 
    vector<vector<string> > barz = g.getSucessores();
    for(int i = 0; i < size; i++){
        utilitario::printList(barz[i]);
    }


    vector<string> componentes = pn.tarjan();
    list<string> pontes = pn.bruteForce();
    cout << "Todas as pontes encontradas: " << endl;
    for(list<string>::iterator it = pontes.begin(); it != pontes.end(); it++){
        cout << *it << endl;
    }
    cout << "TESTE" << endl;
    utilitario::printList(componentes);




    list<string> s;
    s = g.getVertices();

    return 0;
}