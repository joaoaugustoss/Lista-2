#include "utilitario.h"



int utilitario::getIndex(std::list<std::string> _list, std::string _content) {
    int i = 0;
    bool achou = false;
    std::list<std::string>::iterator it = _list.begin();
    for(it = _list.begin(); it != _list.end(); it++, i++){
        std::string content = *it;
        if(_content.compare(content) == 0 ) {
            it = _list.end(); 
            it--;
            achou = true;
        }
    }
    if(!achou) i = -1;
    return --i;
}

bool utilitario::contains(std::list<std::string> _list, std::string _content) {
    bool resp = false;
    std::list<std::string>::iterator it;
    for(it = _list.begin(); it != _list.end(); it++) {
        std::string content = *it;
        if(_content.compare(content) == 0) {
            it = _list.end();
            it--;
            resp = true;
        }
    }
    return resp;
}

bool utilitario::contains(std::vector<std::string> _vector, std::string _content) {
    bool resp = false;
    std::vector<std::string>::iterator it;
    for(it = _vector.begin(); it != _vector.end(); it++) {
        std::string content = *it;
        if(_content.compare(content) == 0) {
            it = _vector.end();
            it--;
            resp = true;
        }
    }
    return resp;
}

void utilitario::printList(std::vector<std::string> _list){
    for(auto element : _list){
        std::cout << element;
    }
    std::cout << '\n';
}

void utilitario::printList(std::list<std::string> _list){
    for(auto element : _list){
        std::cout << element;
    }
    std::cout << '\n';
}