//
// Created by el_dramas on 14/11/23.
//

#include "Guia_tlf.h"

Guia_tlf::Guia_tlf():telefonos(){}

Guia_tlf::Guia_tlf(const Guia_tlf &other): telefonos(other.telefonos){}

Guia_tlf &Guia_tlf::operator=(const Guia_tlf &other) {
    telefonos=other.telefonos;
    return (*this);
}

size_t Guia_tlf::size() const {
    return telefonos.size();
}

bool Guia_tlf::empty() const {
    return telefonos.empty();
}

void Guia_tlf::clear() {
    telefonos.clear();
}

Guia_tlf::iterator Guia_tlf::erase(iterator& iter) {
    iterator it;
    it.it=telefonos.erase(iter.it);
    return it;
}

size_t Guia_tlf::erase(const std::string &clave) {
    return telefonos.erase(clave);
}

void Guia_tlf::insert(const pair<std::string, unsigned int> &dato) {
    telefonos.insert(dato);
}

Guia_tlf::const_iterator Guia_tlf::find(const std::string &clave) const {
   const_iterator iter;
    iter.cit = telefonos.find(clave);
    return iter;
}

Guia_tlf::iterator::iterator():it() {}

Guia_tlf::iterator::iterator(const Guia_tlf::iterator &other):it(other.it) {}

Guia_tlf::iterator &Guia_tlf::iterator::operator=(const Guia_tlf::iterator &other) {
    it=other.it;
    return (*this);
}

Guia_tlf::iterator Guia_tlf::begin() const {
    iterator it;
    it.it=telefonos.begin();

    return it;
}

Guia_tlf::iterator Guia_tlf::end() const {
    iterator it;
    it.it=telefonos.end();

    return it;
}

Guia_tlf::const_iterator::const_iterator():cit() {}

Guia_tlf::const_iterator::const_iterator(Guia_tlf::const_iterator &other):cit(other.cit) {}

Guia_tlf::const_iterator &Guia_tlf::const_iterator::operator=(Guia_tlf::const_iterator &other) {
    cit=other.cit;
    return (*this);
}

bool Guia_tlf::const_iterator::operator==(Guia_tlf::const_iterator &other) const {
    return cit==other.cit;
}

bool Guia_tlf::const_iterator::operator!=(Guia_tlf::const_iterator &other) const {
    return cit!=other.cit;
}

Guia_tlf::const_iterator &Guia_tlf::const_iterator::operator--() {
    this->cit--;
    return (*this);
}

Guia_tlf::const_iterator &Guia_tlf::const_iterator::operator++() {
    this->cit++;
    return (*this);
}

pair<const basic_string<char>, unsigned int> Guia_tlf::iterator::operator*() {
    return *it;
}

Guia_tlf::const_iterator Guia_tlf::cbegin() const {
    const_iterator citer;
    citer.cit=telefonos.begin();
    return citer;
}

Guia_tlf::const_iterator Guia_tlf::cend() const{
    const_iterator citer;
    citer.cit=telefonos.end();
    return citer;
}

void Guia_tlf::Insertar_EN(Guia_tlf &other) const {
    const_iterator citar ;

    for (citar.cit=telefonos.cbegin(); citar.cit != telefonos.cend(); ++citar){
        other.telefonos.insert(*citar.cit);
    }

}

void Guia_tlf::changetlf(const std::string &clave,unsigned int tlf) {
    //Faltan las comprobaciones
    telefonos.at(clave)=tlf;

}

Guia_tlf Guia_tlf::Interseccion(const Guia_tlf &other) const {
    Guia_tlf nueva;
    if(other.empty() || this->empty())return nueva;

    iterator it;

    it=this->begin();

    while(it != this->end()){
        if (other.find((*it).first) != other.cend()){
            nueva.insert(*it);
        }
        ++it;
    }
    return nueva;

}


















