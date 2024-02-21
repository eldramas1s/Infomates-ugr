/*
 * File:   Pais.cpp
 * Author: Lucas Hidalgo Herrera
 * Author: Juan Manuel Fernández García
 *
 */

#include "Pais.h"
///////////////////////////////////////////////////////////////////////
// IMPLEMENTACIÓN CLASE PAIS.
///////////////////////////////////////////////////////////////////////
/*************************************************************/
Pais::Pais(){}

/*************************************************************/
Pais::Pais(const Punto &point, const std::string &name, const std::string &path) {

    //Posibles comprobaciones

    this->p=point;
    this->bandera=path;
    this->pais=name;

}

//////////////////////////
// MÉTODOS DE CONSULTA. //
//////////////////////////

/*************************************************************/
const std::string &Pais::GetBandera() const {
    return this->bandera;
}

/*************************************************************/
const std::string &Pais::GetPais() const {
    return this->pais;
}

/*************************************************************/
const Punto &Pais::GetPunto() const {
    return this->p;
}

///////////////////////////////////
// OPERACIONES DE LA CLASE PAIS. //
///////////////////////////////////
/*************************************************************/
bool Pais::operator==(const Punto &point) const {
    bool iguales;
    if(this->p.GetLat()!=point.GetLat()) iguales=false;
    if(this->p.GetLong()!=point.GetLong()) iguales=false;

    return iguales;
}

/*************************************************************/
bool Pais::operator==(const Pais &other) const {
    return (*this)==other.GetPunto();
}

/*************************************************************/
bool Pais::operator<(const Pais &other) const {
    return this->GetPais()<other.GetPais();
}
/*************************************************************/


void Pais::SetBandera(const std::string &other) {
    this->bandera=other;
}

/*************************************************************/
void Pais::SetPais(const std::string &other) {
    this->pais=other;
}

/*************************************************************/
void Pais::SetPoint(const Punto &other) {
    this->p=other;
}

/*************************************************************/
double Pais::Distancia(const Pais &other) const {
    return this->p.Distancia(other.GetPunto());
}

/*************************************************************/
bool Pais::operator!=(const Pais &other) const {
    return !(*this==other);
}

/*************************************************************/
bool Pais::operator>(const Pais &other) const {
    return (!(*this<other) && !(*this==other));
}

/*************************************************************/
bool Pais::operator<=(const Pais &other) const {
    return !(*this>other);
}

/*************************************************************/
bool Pais::operator>=(const Pais &other) const {
    return !(*this<other);
}

///////////////////////////////////////////////////////////////////////
// OPERADORES DE ENTRADA/SALIDA FLUJO.
///////////////////////////////////////////////////////////////////////

/*************************************************************/
std::istream & operator >> (std::istream& is, Pais& other){
    double lat, lon;
    std::string name, path;

    is>> lat;
    is >> lon;

    Punto p(lat,lon);

    is >> name;
    is >> path;

    Pais aux(p,name,path);

    other=aux;

    return is;
}

/*************************************************************/
std::ostream & operator <<(std::ostream& os, const Pais & pais){
    os << pais.GetPunto().GetLat() << " " << pais.GetPunto().GetLong() << " " << pais.GetPais() << " "
    << pais.GetBandera() << endl;

    return os;
}

