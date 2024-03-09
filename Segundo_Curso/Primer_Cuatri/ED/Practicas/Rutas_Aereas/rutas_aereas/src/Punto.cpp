/*
 * File:   Punto.cpp
 * Author: Lucas Hidalgo Herrera
 * Author: Juan Manuel Fernández García
 *
 */

#include "Punto.h"
#include <iostream>
#include <string>
#include<cmath>
#include <iomanip>

/**********************************************************/
Punto::Punto(double latitud, double longitud): x(latitud), y(longitud) {}

/**********************************************************/
Punto::Punto(const Punto& other): x(other.x), y(other.y) {}

/**********************************************************/
Punto::Punto(const std::string& str)
{
    int lenght_x = str.find(',') - 1;
    int length_y = str.find_first_of(')') - str.find(',') + 1;
    
    x = stod(str.substr(1, lenght_x));
    y= stod(str.substr(str.find(',')+1, length_y));
}

/**********************************************************/
void Punto::SetLat(double l) { x = l; }

/**********************************************************/
void Punto::SetLong(double l) { y = l; }

/**********************************************************/
double Punto::GetLat() const { return x; }

/**********************************************************/
double Punto::GetLong() const { return y; }

/**********************************************************/
double Punto::Distancia(const Punto& other) const
{
    return (std::sqrt((x - other.x )*(x - other.x ) +
           (y - other.y )*(y - other.y)));
}

/**********************************************************/
bool Punto::operator==(const Punto& punto)
{
    return (x == punto.x && y == punto.y);
}

/**********************************************************/
bool Punto::operator!=(const Punto& punto)
{
    return (!(*this == punto));
}

///////////////////////////////////////////////////////////////////////
// OPERADORES DE ENTRADA/SALIDA FLUJO.
///////////////////////////////////////////////////////////////////////

/**********************************************************/
std::ostream& operator<<(std::ostream& os, const Punto& punto)
{
    os << "(" << punto.GetLat() << ","
       << punto.GetLong() << ")";
    return os;
}

/**********************************************************/
std::istream& operator>>(std::istream& is, Punto& punto)
{
    std::string str;
    is >> str;
    punto = Punto(str);
    
    return is;
}