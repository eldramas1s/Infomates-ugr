/*
 * File:   Mundo.cpp
 * Author: Lucas Hidalgo Herrera
 * Author: Juan Manuel Fernández García
 *
 */
#include "Mundo.h"
#include <set>
#include <fstream>
#include <iostream>
#include "Pais.h"

///////////////////////////////////////////////////////////////////////
// IMPLEMENTACIÓN CLASE MUNDO.
///////////////////////////////////////////////////////////////////////

const std::string Mundo::CABECERA= "# Latitud           Longitud            Pais        Bandera";
/*********************************************************************/
Mundo::Mundo() {}

/*********************************************************************/
Mundo::Mundo(const Mundo &other):mundo(other.mundo) {}

/*********************************************************************/
Mundo::Mundo(const char fich_Mundo[]) {
    load(fich_Mundo);
}

//////////////////////////
// MÉTODOS DE CONSULTA. //
//////////////////////////

/*********************************************************************/
bool Mundo::empty() const {
    return this->mundo.empty();
}
/*********************************************************************/

unsigned int Mundo::size() const {
    return this->mundo.size();
}


///////////////////////////////////
// OPERACIONES DE LA CLASE MUNDO. //
///////////////////////////////////

/*********************************************************************/
void Mundo::clear() {
    mundo.clear();
}

/*********************************************************************/

bool Mundo::erase(const Pais &pais) {
    size_t s=mundo.erase(pais);

    return s>0;
}

/*********************************************************************/
Mundo::iterator Mundo::erase(const_iterator & pos) {
    Mundo:iterator iter;
    iter.it=mundo.erase(pos.cit);
    return iter;
}

/*********************************************************************/
Mundo::iterator Mundo::find(const Pais &pais) {
    Mundo::iterator iter;
    iter.it=mundo.find(pais);

    return iter;
}

/*********************************************************************/
Mundo::iterator Mundo::find(const Punto& punto)
{
    iterator iter = begin();
    bool seguir = true;
    
    while(iter != end() && seguir)
    {
        Punto p = (*iter).GetPunto();
        if(p == punto) seguir = false;
        
        else ++iter;
    }
    
    return iter;
}

/*********************************************************************/
Mundo::const_iterator Mundo::cfind(const Pais &pais) {
    Mundo::const_iterator citer;

    citer.cit=mundo.find(pais);

    return citer;
}

/*********************************************************************/
Mundo::iterator Mundo::insert(const Pais &pais) {
    Mundo::iterator iter;
    iter.it=mundo.insert(mundo.cbegin(),pais);
    return iter;
}

/*********************************************************************/
void Mundo::load(const char fich_Mundo[]) {
    fstream inputfile;

    //Abrimos archivo y comprobamos que se ha abierto.
    inputfile.open(fich_Mundo);
    if(!inputfile){
        string error = "Error, no se pudo abrir el fichero ";
        error += fich_Mundo;
        throw std::ios_base::failure(error);
    }

    //Limpiamos el objeto.
    clear();

    string magic;

    getline(inputfile, magic);
    
    //std::cout << magic << std::endl;
    //Comprobamos el caracter magico
    if(magic!=CABECERA){
        std::string message = "Error, no se encontró el caracter mágico en ";
        message += std::string(fich_Mundo);

        throw std::invalid_argument(message);
    }

    inputfile >> (*this);
    inputfile.close();

}

/*********************************************************************/
void Mundo::save(const char fich_Mundo[]) const {
    std::ofstream outputstream;

    outputstream.open(fich_Mundo);

    if(!outputstream){
        std::string error = "Error, no se pudo abrir el fichero ";
        error += fich_Mundo;
        throw std::ios_base::failure(error);
    }

    outputstream << CABECERA << endl;
    outputstream << (*this);

    outputstream.close();
}

///////////////////////////////////////////////////////////////////////
// IMPLEMENTACIÓN CLASE ITERATOR.
///////////////////////////////////////////////////////////////////////

/*********************************************************************/
Mundo::iterator::iterator() {}

/*********************************************************************/
Mundo::iterator::iterator(const Mundo::iterator &iter):it(iter.it) {}

/*********************************************************************/

bool Mundo::iterator::operator!=(const Mundo::iterator &other) const {
    return it!=other.it;
}

/*********************************************************************/
bool Mundo::iterator::operator==(const Mundo::iterator &other) const {
    return it==other.it;
}

/*********************************************************************/
Mundo::iterator &Mundo::iterator::operator++() {
    ++it;
    return *this;
}

/*********************************************************************/
Mundo::iterator &Mundo::iterator::operator--() {
    --it;
    return *this;
}
/*********************************************************************/
Mundo::iterator &Mundo::iterator::operator=(const Mundo::iterator &other) {
    it=other.it;
    return *this;
}

/*********************************************************************/
const Pais& Mundo::iterator::operator*() const{
    return (*it);
}

/*********************************************************************/
Mundo::iterator Mundo::begin() {
    Mundo::iterator iter;
    iter.it=mundo.begin();
    return iter;
}

/*********************************************************************/
Mundo::iterator Mundo::end() {
    Mundo::iterator iter;
    iter.it=mundo.end();
    return iter;
}

///////////////////////////////////////////////////////////////////////
// IMPLEMENTACIÓN CLASE CONST_ITERATOR.
///////////////////////////////////////////////////////////////////////

/*********************************************************************/
Mundo::const_iterator::const_iterator() {}

/*********************************************************************/
Mundo::const_iterator::const_iterator(const Mundo::const_iterator &other):cit(other.cit) {}

/*********************************************************************/
Mundo::const_iterator &Mundo::const_iterator::operator=(const Mundo::const_iterator &other) {
    cit=other.cit;
    return (*this);
}

/*********************************************************************/
Mundo::const_iterator &Mundo::const_iterator::operator++() {
    ++cit;
    return *this;
}

/*********************************************************************/
Mundo::const_iterator &Mundo::const_iterator::operator--() {
    --cit;
    return *this;
}

/*********************************************************************/
bool Mundo::const_iterator::operator==(const Mundo::const_iterator &other) const {
    return cit==other.cit;
}

/*********************************************************************/
bool Mundo::const_iterator::operator!=(const Mundo::const_iterator &other) const {
    return cit!=other.cit;
}

/*********************************************************************/
const Pais& Mundo::const_iterator::operator*() const {
    return (*cit);
}

/*********************************************************************/
Mundo::const_iterator Mundo::cbegin() const {
    Mundo::const_iterator citer;
    citer.cit=mundo.cbegin();
    return citer;
}

/*********************************************************************/
Mundo::const_iterator Mundo::cend() const {
    Mundo::const_iterator citer;
    citer.cit=mundo.cend();
    return citer;
}

///////////////////////////////////////////////////////////////////////
// OPERADORES DE ENTRADA/SALIDA FLUJO.
///////////////////////////////////////////////////////////////////////

/*********************************************************************/
std::ostream& operator<<(std::ostream& os, const Mundo& mundo){
    for(Mundo::const_iterator cit=mundo.cbegin(); cit!=mundo.cend(); ++cit){
        os << *cit << endl;
    }

    return os;
}

/*********************************************************************/
std::istream& operator>>(std::istream& is, Mundo& mundo){
    Pais aux;
    while(is >> aux){
        mundo.insert(aux);
    }
    return is;
}