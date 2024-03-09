/*
 * File:   Ruta.cpp
 * Author: Lucas Hidalgo Herrera
 * Author: Juan Manuel Fernández García
 *
 */

#include "Ruta.h"
#include "Punto.h"
#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>

///////////////////////////////////////////////////////////////////////
// IMPLEMENTACIÓN CLASE RUTA.
///////////////////////////////////////////////////////////////////////

/*********************************************************************/
Ruta::Ruta() {}

/*********************************************************************/
Ruta::Ruta(const Ruta& other): ruta(other.ruta), id(other.id) {}

/*********************************************************************/
Ruta::Ruta(const char fich_ruta[])
{
    load(fich_ruta);
}

//////////////////////////
// MÉTODOS DE CONSULTA. //
//////////////////////////

/*********************************************************************/
Punto& Ruta::operator[](int pos)
{
    return (ruta[pos]);
}

/*********************************************************************/
const Punto& Ruta::operator[](int pos) const
{
    return (ruta[pos]);
}

/*********************************************************************/
Punto& Ruta::at(int pos)
{
    if(pos < 0 || pos >= ruta.size())
    {
        throw std::out_of_range("Error en at: Posición incorrecta.");
    }
    
    return (ruta.at(pos));
}

/*********************************************************************/
const Punto& Ruta::at(int pos) const
{
    if(pos < 0 || pos >= ruta.size())
    {
        throw std::out_of_range("Error en at: Posición incorrecta.");
    }
    
    return (ruta.at(pos));
}

/*********************************************************************/
bool Ruta::empty() const
{
    return (ruta.empty());
}

/*********************************************************************/
unsigned int Ruta::size() const
{
    return (ruta.size());
}

/*********************************************************************/
const std::string& Ruta::GetIDRuta() const
{
    return id;
}

///////////////////////////////////
// OPERACIONES DE LA CLASE RUTA. //
///////////////////////////////////

/*********************************************************************/
void Ruta::SetIDRuta(const std::string& str)
{
    id = str;
}

/*********************************************************************/
Ruta::iterator Ruta::erase(Ruta::const_iterator pos)
{
    Ruta::iterator iter;
    iter.it = ruta.erase(pos.it);
    
    return iter;
}

/*********************************************************************/
void Ruta::clear()
{
    ruta.clear();
}

/*********************************************************************/
void Ruta::push_back(const Punto& punto)
{
    ruta.push_back(punto);
}

/*********************************************************************/
Ruta::iterator Ruta::insert(const Ruta::const_iterator& pos, const Punto& punto)
{
    Ruta::iterator iter;
    iter.it = ruta.insert(pos.it, punto);
    
    return iter;
}

/*********************************************************************/
void Ruta::load(const char fich_ruta[])
{
    std::ifstream input_stream;
    input_stream.open(fich_ruta);
    
    if(!input_stream) {
        
        std::string error = "Error, no se pudo abrir el fichero ";
        error += fich_ruta;
        throw std::ios_base::failure(error);
    }
    
    clear();
    
    input_stream >> id;
    
    int tamanio;
    input_stream >> tamanio;
    ruta.resize(tamanio);
    
    for(int i = 0; i < tamanio; ++i) {
        
        Punto p;
        input_stream >> p;
        
        ruta[i] = p;
    }
    
    input_stream.close();
}

/*********************************************************************/
void Ruta::save(const char fich_ruta[]) const
{
    std::ofstream output_stream;
    output_stream.open(fich_ruta);
    
    if(!output_stream) {
        
        std::string error = "Error, no se pudo abrir el fichero ";
        error += fich_ruta;
        throw std::ios_base::failure(error);
    }
    
    output_stream << id << " " << ruta.size() << " ";
    
    for(vector<Punto>::const_iterator it = ruta.begin(); it != ruta.end(); ++it)
    {
        output_stream << *it << " ";
    }
    
    output_stream.close();
}

///////////////////////////////////////////////////////////////////////
// IMPLEMENTACIÓN CLASE ITERATOR.
///////////////////////////////////////////////////////////////////////

/*********************************************************************/
Ruta::iterator::iterator() {}

/*********************************************************************/
Ruta::iterator::iterator(const Ruta::iterator& other):
        it(other.it)
{}

/*********************************************************************/
Ruta::iterator& Ruta::iterator::operator=(const Ruta::iterator& other)
{
    it = other.it;
    return (*this);
}

/*********************************************************************/
bool Ruta::iterator::operator==(const Ruta::iterator& other) const
{
    return (it == other.it);
}

/*********************************************************************/
bool Ruta::iterator::operator!=(const Ruta::iterator& other) const
{
    return (it != other.it);
}

/*********************************************************************/
Punto& Ruta::iterator::operator*()
{
    return (*it);
}

/*********************************************************************/
Ruta::iterator& Ruta::iterator::operator++()
{
    ++it;

    return (*this);
}

/*********************************************************************/
Ruta::iterator& Ruta::iterator::operator--()
{
    --it;

    return (*this);
}

/*********************************************************************/
Ruta::iterator Ruta::begin()
{
    iterator iter;
    iter.it = ruta.begin();

    return iter;
}

/*********************************************************************/
Ruta::iterator Ruta::end()
{
    iterator iter;
    iter.it = ruta.end();

    return iter;
}

///////////////////////////////////////////////////////////////////////
// IMPLEMENTACIÓN CLASE CONST_ITERATOR.
///////////////////////////////////////////////////////////////////////

/*********************************************************************/
Ruta::const_iterator::const_iterator() {}

/*********************************************************************/
Ruta::const_iterator::const_iterator(const Ruta::const_iterator& other):
        it(other.it)
{}

/*********************************************************************/
Ruta::const_iterator& Ruta::const_iterator::operator=(const Ruta::const_iterator& other)
{
    it = other.it;
    return (*this);
}

/*********************************************************************/
bool Ruta::const_iterator::operator==(const Ruta::const_iterator& other) const
{
    return (it == other.it);
}

/*********************************************************************/
bool Ruta::const_iterator::operator!=(const Ruta::const_iterator& other) const
{
    return (it != other.it);
}

/*********************************************************************/
const Punto& Ruta::const_iterator::operator*() const
{
    return (*it);
}

/*********************************************************************/
Ruta::const_iterator& Ruta::const_iterator::operator++()
{
    ++it;

    return (*this);
}

/*********************************************************************/
Ruta::const_iterator& Ruta::const_iterator::operator--()
{
    --it;

    return (*this);
}

/*********************************************************************/
Ruta::const_iterator Ruta::cbegin() const
{
    const_iterator iter;
    iter.it = ruta.cbegin();

    return iter;
}

/*********************************************************************/
Ruta::const_iterator Ruta::cend() const
{
    const_iterator iter;
    iter.it = ruta.cend();

    return iter;
}

///////////////////////////////////////////////////////////////////////
// OPERADORES DE ENTRADA/SALIDA FLUJO.
///////////////////////////////////////////////////////////////////////

/**********************************************************/
std::ostream& operator<<(std::ostream& os, const Ruta& ruta)
{
    os << ruta.GetIDRuta() << " " << ruta.size() << " ";
    
    for(Ruta::const_iterator it = ruta.cbegin(); it != ruta.cend(); ++it)
    {    
        os << *it << " ";
    }
    
    return os;
}

/**********************************************************/
std::istream& operator>>(std::istream& is, Ruta& ruta)
{
    ruta.clear();
    
    std::string str;
    is >> str;
    
    ruta.SetIDRuta(str);
    
    int tam = 0;
    is >> tam;
    
    for(int i = 0; i < tam; ++i)
    {
        Punto p;
        is >> p;
        ruta.push_back(p);
    }
    
    return is;
}