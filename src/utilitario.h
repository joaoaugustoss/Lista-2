#ifndef UTILITARIO_H
#define UTILITARIO_H

#include <iostream>
#include <list>
#include <vector>

class utilitario{
    public:
        static int getIndex(std::list<std::string>, std::string);
        static bool contains(std::vector<std::string>, std::string);
        static bool contains(std::list<std::string>, std::string);
        static void printList(std::vector<std::string>);
        static void printList(std::list<std::string>);
        

};
#endif // UTILITARIO_H