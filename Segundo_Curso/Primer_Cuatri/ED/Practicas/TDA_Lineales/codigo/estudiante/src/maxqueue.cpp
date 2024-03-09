/**
 * @file maxqueue.cpp
 * @brief  Archivo de implementación del TDA MaxQueue
 * @author
 */

#include "maxqueue.h"

void maxqueue::volcar(stack<pair<int, int>> &c) {
    while(!this->empty()){
        c.push(this->cola.top());
        this->pop();
    }
}
pair<int, int> &maxqueue::front() {
    return this->cola.top();
}

const pair<int, int> &maxqueue::front() const {
    return this->cola.top();
}

void maxqueue::pop() {
    this->cola.pop();
}

void maxqueue::push(pair<int, int> p) {
    int max_new=this->front().second;

    if (p.second>max_new){
        max_new=p.second;
    }

    stack <pair<int,int>> aux;

    this->volcar(aux);
    this->cola.push(p);
    while(!this->empty()){

        this->cola.push(aux.top());
        this->front().second=max_new;
        aux.pop();
    }
    
}

bool maxqueue::empty() const {
    return this->cola.empty();
}

ostream& operator<<(ostream& modo,const pair <int,int> &p){

    modo<<p.first << " , " << p.second << endl;
    return modo;

}