#include <iostream>
#include <string>
#include <vector>
#include <set>

#include "Dictionary_multi.h"

Dictionary_multi::Dictionary_multi() {}
Dictionary_multi::Dictionary_multi(const Dictionary_multi &other) {
    this->words=other.words;
}
int Dictionary_multi::count(const std::string &clave) const {
    return this->words.count(clave);
}

pair<multiset<string>::iterator,multiset<string>::iterator> Dictionary_multi::buscar(const std::string &clave) const {
    pair <multiset<string>::iterator,multiset<string>::iterator> resultado;

    resultado=words.equal_range(clave);

    return resultado;
}

void Dictionary_multi::clear() { words.clear();}

bool Dictionary_multi::empty() const {return words.empty();}

size_t Dictionary_multi::size() const {
    size_t result = 0;
    result = words.size();
    return result;
}

Dictionary_multi::iterator::iterator(): el_iterador() {}

Dictionary_multi::iterator::iterator(const Dictionary_multi::iterator &other) : el_iterador(other.el_iterador){}

Dictionary_multi::iterator &Dictionary_multi::iterator::operator=(const Dictionary_multi::iterator &other) {
    el_iterador=other.el_iterador;
    return (*this);
}

bool Dictionary_multi::iterator::operator==(const Dictionary_multi::iterator &other) const {
    return el_iterador==other.el_iterador;
}
bool Dictionary_multi::iterator::operator!=(const Dictionary_multi::iterator &other) const {
    return !((*this)==other);
}

Dictionary_multi::iterator &Dictionary_multi::iterator::operator++() {
    ++el_iterador;
    return *this;
}

Dictionary_multi::iterator &Dictionary_multi::iterator::operator--() {
    --el_iterador;
    return (*this);
}

string &Dictionary_multi::iterator::operator*() {
    return const_cast<string &>(*el_iterador);
}

Dictionary_multi::iterator Dictionary_multi::erase(const std::string &clave) {
    iterator it;
    multiset<string>::iterator iter=words.lower_bound(clave);
    while(iter!=words.end()){
        it.el_iterador=words.erase(iter);
    };
    return it;
}

Dictionary_multi::iterator Dictionary_multi::begin() const {
    iterator it;
    it.el_iterador=words.begin();
    return it;
}

Dictionary_multi::iterator Dictionary_multi::end() const {
    iterator it;
    it.el_iterador=words.end();
    return it;
}

Dictionary_multi::const_iterator::const_iterator():iter_const() {}

Dictionary_multi::const_iterator::const_iterator(const Dictionary_multi::const_iterator &other): iter_const(other.iter_const){}

Dictionary_multi::const_iterator &Dictionary_multi::const_iterator::operator++() {
    iter_const++;
    return (*this);
}

Dictionary_multi::const_iterator &Dictionary_multi::const_iterator::operator--() {
    iter_const--;
    return (*this);
}

bool Dictionary_multi::const_iterator::operator==(const Dictionary_multi::const_iterator &other) const {
    return iter_const==other.iter_const;
}

bool Dictionary_multi::const_iterator::operator!=(const Dictionary_multi::const_iterator &other) const {
    return !(*this==other);
}

Dictionary_multi::const_iterator &Dictionary_multi::const_iterator::operator=(const Dictionary_multi::const_iterator &other) {
    iter_const=other.iter_const;
    return (*this);
}

const string &Dictionary_multi::const_iterator::operator*() const {
    return const_cast<const string &> (*iter_const);
}

Dictionary_multi::const_iterator Dictionary_multi::cbegin() {
    const_iterator cit;
    cit.iter_const=words.cbegin();
    return cit;
}

Dictionary_multi::const_iterator Dictionary_multi::cend() {
    const_iterator cit;
    cit.iter_const=words.cend();
    return cit;
}

vector<string> Dictionary_multi::wordsOfLength(int longitud) const {

    vector<string> wol;

    for (iterator it = (*this).begin(); it != (*this).end(); ++it)
        if ((*it).length() == longitud) wol.push_back(*it);

    return wol;
}

int Dictionary_multi::getOccurrences(char c) const {
    int counter=0;
    iterator it;

        for (it=(*this).begin(); it!=(*this).end(); ++it)
            counter+= Ocurrences(*it,c);

    return counter;
}

int Dictionary_multi::Ocurrences(const std::string &cad, char c) const {
    int counter=0;
    for (int i=0; i< cad.length(); ++i)
        if(cad.at(i)==c) ++counter;
    return counter;
}

Dictionary_multi::iterator Dictionary_multi::insert(const string & clave) {
    iterator iter;
    pair <bool,multiset<string>::iterator> result;

    iter.el_iterador=words.insert(clave);

    return iter;
}

void Dictionary_multi::Aniade(const Dictionary_multi &other) {
    iterator it=other.begin();

    if(other.size()>0){
        while(it != other.end()){
            if(this->count(*it) == 0){
                this->insert(*it);
            }
            ++it;
        }
    }
}

void Dictionary_multi::Load(const char *pathname) {

    if(!this->empty()) this->clear();

    ifstream input_stream;

    input_stream.open(pathname);
    string cad;
    if(input_stream.is_open()){
        while(cin>>cad){
            this->insert(cad);
        }
    }
    input_stream.close();

}
ostream & operator<<(ostream& output, const Dictionary_multi &dictionary){
    Dictionary_multi::iterator it=dictionary.begin();
    while(it!=dictionary.end()){
        output << *it << ",";
        ++it;
    }
    return output;
}
