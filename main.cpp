#include <iostream>
//#include "graph.h"
#include "ponte.h"

using namespace std;

int main(){
    graph g;
    list<string> foo;
    foo.push_back("a");
    foo.push_back("b");
    foo.push_back("c");
    foo.push_back("d");
    g.setVertices(foo);
    foo.clear();
    foo.push_back("ab");
    foo.push_back("bc");
    foo.push_back("cd");
    foo.push_back("da");
    g.setArestas(foo);
    ponte p = ponte(g);



    p.bruteForce();

    list<string> s;
    s = g.getVertices();
    // s.push_back("append");
    // s.push_back("list");
    // s.push_back("cpp");
    /*for(string i : s){
        cout << i << endl;
    }*/
    return 0;
}