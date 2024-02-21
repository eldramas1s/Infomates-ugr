#include "Dictionary.h"
#include <string>
#include <vector>
#include <fstream>
#include <set>
#include <iostream>

///////////////////////////////////////////////////////////////////////
// IMPLEMENTACIÓN CLASE DICTIONARY.
///////////////////////////////////////////////////////////////////////

/*********************************************************************/
Dictionary::Dictionary() {}

/*********************************************************************/
Dictionary::Dictionary(const Dictionary& other): words(other.words) {}

/*********************************************************************/
bool Dictionary::exists(const std::string& palabra) const
{
    std::set<std::string>::iterator it = words.find(palabra);

    return (it != words.end());
}

/*********************************************************************/
Dictionary::Dictionary(const char d_file[])
{
    load(d_file);
}

/*********************************************************************/
bool Dictionary::insert(const std::string& palabra)
{
    std::pair<std::set<std::string>::iterator, bool> resultado = words.insert(palabra);

    return resultado.second;
}

/*********************************************************************/
bool Dictionary::erase(const std::string& palabra)
{
    return (words.erase(palabra) == 1);
}

/*********************************************************************/
void Dictionary::clear()
{
    words.clear();
}

/*********************************************************************/
bool Dictionary::empty() const
{
    return (words.empty());
}

/*********************************************************************/
unsigned int Dictionary::size() const
{
    return words.size();
}

/*********************************************************************/
std::vector<std::string> Dictionary::wordsOfLength(int length)
{
    std::vector<std::string> v;
    std::set<std::string>::iterator it;
    
    for(it = words.begin(); it != words.end(); ++it)
    {
        if((*it).length() == length) v.push_back(*it);
    }
    
    return v;
}

/*********************************************************************/
int Dictionary::getOcurrences(const char c) const
{
    int num_ocurrencias = 0;
    std::set<std::string>::iterator it;
    
    for(it = words.begin(); it != words.end(); ++it)
    {
        std::string str = *it;
        int length = str.length();
        
        for(int i = 0; i < length; ++i)
        {
            if(str.at(i) == c) num_ocurrencias++;
        }
    }
    
    return num_ocurrencias;
}

/*********************************************************************/
void Dictionary::load(const char d_file[])
{
    std::ifstream input_stream;
    input_stream.open(d_file);
    
    if(!input_stream) {
        
        std::string error = "Error, no se pudo abrir el fichero ";
        error += d_file;
        throw std::ios_base::failure(error);
    }
    
    words.clear();
    
    std::string str;
    while(getline(input_stream, str)) {
        
        words.insert(str);
    }
    
    input_stream.close();
}

/*********************************************************************/
void Dictionary::aniade(const Dictionary& dic)
{
    std::set<std::string>::iterator it;
    
    for(it = dic.words.begin(); it != dic.words.end(); ++it)
    {
        words.insert(*it);
    }
}

///////////////////////////////////////////////////////////////////////
// IMPLEMENTACIÓN CLASE ITERATOR.
///////////////////////////////////////////////////////////////////////

/*********************************************************************/
Dictionary::iterator::iterator() {}

/*********************************************************************/
Dictionary::iterator::iterator(const Dictionary::iterator& other):
        el_iterador(other.el_iterador)
{}

/*********************************************************************/
Dictionary::iterator& Dictionary::iterator::operator=(const Dictionary::iterator& other)
{
    el_iterador = other.el_iterador;
    return (*this);
}

/*********************************************************************/
bool Dictionary::iterator::operator==(const Dictionary::iterator& other) const
{
    return (el_iterador == other.el_iterador);
}

/*********************************************************************/
bool Dictionary::iterator::operator!=(const Dictionary::iterator& other) const
{
    return (el_iterador != other.el_iterador);
}

/*********************************************************************/
std::string& Dictionary::iterator::operator* ()
{
    return ((std::string&)*el_iterador);
}

/*********************************************************************/
Dictionary::iterator& Dictionary::iterator::operator++()
{
    ++el_iterador;

    return (*this);
}

/*********************************************************************/
Dictionary::iterator& Dictionary::iterator::operator--()
{
    --el_iterador;

    return (*this);
}

/*********************************************************************/
Dictionary::iterator Dictionary::begin()
{
    iterator it;
    it.el_iterador = words.begin();

    return it;
}

/*********************************************************************/
Dictionary::iterator Dictionary::end()
{
    iterator it;
    it.el_iterador = words.end();

    return it;
}

///////////////////////////////////////////////////////////////////////
// IMPLEMENTACIÓN CLASE CONST_ITERATOR.
///////////////////////////////////////////////////////////////////////

/*********************************************************************/
Dictionary::const_iterator::const_iterator() {}

/*********************************************************************/
Dictionary::const_iterator::const_iterator(const Dictionary::const_iterator& other):
        el_iterador(other.el_iterador)
{}

/*********************************************************************/
Dictionary::const_iterator& Dictionary::const_iterator::operator=
(const Dictionary::const_iterator& other)
{
    el_iterador = other.el_iterador;
    return (*this);
}

/*********************************************************************/
bool Dictionary::const_iterator::operator==(const const_iterator& other) const
{
    return (el_iterador == other.el_iterador);
}

/*********************************************************************/
bool Dictionary::const_iterator::operator!=(const const_iterator& other) const
{
    return (el_iterador != other.el_iterador);
}

/*********************************************************************/
const std::string& Dictionary::const_iterator::operator*() const
{
    return ((std::string&)*el_iterador);
}

/*********************************************************************/
Dictionary::const_iterator& Dictionary::const_iterator::operator++()
{
    ++el_iterador;

    return (*this);
}

/*********************************************************************/
Dictionary::const_iterator& Dictionary::const_iterator::operator--()
{
    --el_iterador;

    return (*this);
}

/*********************************************************************/
Dictionary::const_iterator Dictionary::cbegin() const
{
    const_iterator it;
    it.el_iterador = words.begin();

    return it;
}

/*********************************************************************/
Dictionary::const_iterator Dictionary::cend() const
{
    const_iterator it;
    it.el_iterador = words.end();

    return it;
}

/*********************************************************************/
std::ostream& operator<<(std::ostream& os, const Dictionary& d)
{
    for(Dictionary::const_iterator it = d.cbegin(); it != d.cend(); ++it)
    {
        os << *it << std::endl;
    }
    
    return os;
}