/*
 * File:   Almacen.cpp
 * Author: Lucas Hidalgo Herrera
 * Author: Juan Manuel Fernández García
 *
 */
#include "Almacen.h"
#include "Ruta.h"
#include "Punto.h"
#include <vector>
#include <iomanip>
#include <algorithm>

///////////////////////////////////////////////////////////////////////
// IMPLEMENTACIÓN CLASE ALMACÉN.
///////////////////////////////////////////////////////////////////////

/*********************************************************************/
const std::string Almacen::MAGIC_STRING = "#Rutas";

/*********************************************************************/
Almacen::Almacen() {}

/*********************************************************************/
Almacen::Almacen(const Almacen& orig): store(orig.store) {}

/*********************************************************************/
Almacen::Almacen(const char fich_almacen[])
{
    load(fich_almacen);
}

//////////////////////////
// MÉTODOS DE CONSULTA. //
//////////////////////////

/*********************************************************************/
Ruta& Almacen::operator[](const std::string& id)
{
    return (store[id]);
}

/*********************************************************************/
Ruta& Almacen::at(const std::string& id) {
    
    return(store.at(id));
}

/*********************************************************************/
const Ruta& Almacen::at(const std::string& id) const
{
    return(store.at(id));
}

/*********************************************************************/
bool Almacen::empty() const
{
    return (store.empty());
}

/*********************************************************************/
unsigned int Almacen::size() const
{
    return (store.size());
}

//////////////////////////////////////
// OPERACIONES DE LA CLASE ALMACÉN. //
//////////////////////////////////////

/*********************************************************************/
void Almacen::clear() { store.clear(); }

/*********************************************************************/
Almacen::iterator Almacen::erase(Almacen::const_iterator pos)
{
    Almacen::iterator iter;
    iter.it = store.erase(pos.it);
    
    return iter;
}

/*********************************************************************/
bool Almacen::push_back(const Ruta& ruta)
{
    std::pair<std::string, Ruta> par_id_ruta(ruta.GetIDRuta(), ruta);
    
    return (store.insert(par_id_ruta)).second;
}

/*********************************************************************/
std::pair<Almacen::iterator, bool> Almacen::insert(const Almacen::const_iterator& pos, const Ruta& ruta)
{
    const std::pair<std::string, Ruta> par_id_ruta(ruta.GetIDRuta(), ruta);
    std::pair<std::map<std::string, Ruta>::iterator, bool> p = store.insert(par_id_ruta);
    
    std::pair<Almacen::iterator, bool> resultado;
    
    resultado.first.it = p.first;
    resultado.second = p.second;
    
    return resultado;
}

/*********************************************************************/
void Almacen::load(const char fich_almacen[])
{
    std::ifstream input_stream;
    input_stream.open(fich_almacen);
    
    if(!input_stream) {
        
        std::string error = "Error, no se pudo abrir el fichero ";
        error += fich_almacen;
        throw std::ios_base::failure(error);
    }
    
    // Comprobamos que está la palabra mágica.
    std::string possible_magic_string;
    input_stream >> possible_magic_string;
    
    if(possible_magic_string != MAGIC_STRING)
    {
        
        std::string message = "Error, no se encontró la palabra mágica en ";
        message += std::string(fich_almacen);
        
        throw std::invalid_argument(message);
    }
    
    clear();
    
    input_stream >> (*this);
    input_stream.close();
}

/*********************************************************************/
void Almacen::save(const char fich_almacen[]) const
{
    std::ofstream output_stream;
    output_stream.open(fich_almacen);
    
    if(!output_stream) {
        
        std::string error = "Error, no se pudo abrir el fichero ";
        error += fich_almacen;
        throw std::ios_base::failure(error);
    }
    
    output_stream << MAGIC_STRING << std::endl;
    
    for(const_iterator it = cbegin(); it != cend(); ++it)
    {
        output_stream << *it << endl;
    }
    
    output_stream.close();
}

///////////////////////////////////////////////////////////////////////
// IMPLEMENTACIÓN CLASE ITERATOR.
///////////////////////////////////////////////////////////////////////

/*********************************************************************/
Almacen::iterator::iterator() {}

/*********************************************************************/
Almacen::iterator::iterator(const Almacen::iterator& other):
        it(other.it)
{}

/*********************************************************************/
Almacen::iterator& Almacen::iterator::operator=(const Almacen::iterator& other)
{
    it = other.it;
    return (*this);
}

/*********************************************************************/
bool Almacen::iterator::operator==(const Almacen::iterator& other) const
{
    return (it == other.it);
}

/*********************************************************************/
bool Almacen::iterator::operator!=(const Almacen::iterator& other) const
{
    return (it != other.it);
}

/*********************************************************************/
Ruta& Almacen::iterator::operator*()
{
    return (*it).second;
}

/*********************************************************************/
Almacen::iterator& Almacen::iterator::operator++()
{
    ++it;

    return (*this);
}

/*********************************************************************/
Almacen::iterator& Almacen::iterator::operator--()
{
    --it;

    return (*this);
}

/*********************************************************************/
Almacen::iterator Almacen::begin()
{
    iterator iter;
    iter.it = store.begin();

    return iter;
}

/*********************************************************************/
Almacen::iterator Almacen::end()
{
    iterator iter;
    iter.it = store.end();

    return iter;
}

///////////////////////////////////////////////////////////////////////
// IMPLEMENTACIÓN CLASE CONST_ITERATOR.
///////////////////////////////////////////////////////////////////////

/*********************************************************************/
Almacen::const_iterator::const_iterator() {}

/*********************************************************************/
Almacen::const_iterator::const_iterator(const Almacen::const_iterator& other):
        it(other.it)
{}

/*********************************************************************/
Almacen::const_iterator& Almacen::const_iterator::operator=
(const Almacen::const_iterator& other)
{
    it = other.it;
    return (*this);
}

/*********************************************************************/
bool Almacen::const_iterator::operator==(const Almacen::const_iterator& other) const
{
    return (it == other.it);
}

/*********************************************************************/
bool Almacen::const_iterator::operator!=(const Almacen::const_iterator& other) const
{
    return (it != other.it);
}

/*********************************************************************/
const Ruta& Almacen::const_iterator::operator*() const
{
    return (*it).second;
}

/*********************************************************************/
Almacen::const_iterator& Almacen::const_iterator::operator++()
{
    ++it;

    return (*this);
}

/*********************************************************************/
Almacen::const_iterator& Almacen::const_iterator::operator--()
{
    --it;

    return (*this);
}

/*********************************************************************/
Almacen::const_iterator Almacen::cbegin() const
{
    const_iterator iter;
    iter.it = store.cbegin();

    return iter;
}

/*********************************************************************/
Almacen::const_iterator Almacen::cend() const
{
    const_iterator iter;
    iter.it = store.cend();

    return iter;
}

///////////////////////////////////////////////////////////////////////
// OPERADORES DE ENTRADA/SALIDA FLUJO.
///////////////////////////////////////////////////////////////////////

/*********************************************************************/
std::ostream& operator<<(std::ostream& os, const Almacen& almacen)
{
    for(Almacen::const_iterator it = almacen.cbegin(); it != almacen.cend(); ++it)
    {
        os << *it << std::endl;
    }
    
    return os;
}

/*********************************************************************/
std::istream& operator>>(std::istream& is, Almacen& almacen)
{
    almacen.clear();
    Ruta aux;
    
    while(is >> aux) almacen.push_back(aux);
    
    return is;
}