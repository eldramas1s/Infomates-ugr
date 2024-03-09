/**
 * @file maxstack.cpp
 * @brief  Archivo de implementación del TDA MaxStack
 * @author
 */

#include "maxstack.h"

void maxstack::push(pair<int, int> p) {
    if(this->top().second>p.second){
        p.second=this->top().second;
    }
    pila.push(p);
    for (int i=0; i<this->pila.size()/sizeof (pair<int,int>) -1; ++i){
       pila.push(pila.front());
       pila.pop();
    }

}

bool maxstack::empty() const {
    return this->pila.empty();
}

void maxstack::pop() {
    this->pila.pop();
}

pair<int, int> &maxstack::top() {
    return this->pila.front();
}

const pair<int, int> &maxstack::top() const {
    return this->pila.front();
}
