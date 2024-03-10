/* 
 * File:   ruta_aerea.cpp
 * Author: Lucas Hidalgo Herrera
 * Author: Juan Manuel Fernández García
 *
 */

#include "Almacen.h"
#include "Imagen.h"
#include "Mundo.h"
#include <iostream>

typedef Ruta::const_iterator ruta_cit;

using namespace std;

int main(int argc, char** argv) {

    if (argc!=8){
        
        cout<<"Los parametros son:"<<endl;
        cout<<"1.-Fichero con la informacion de los paises"<<endl;
        cout<<"2.-Nombre de la imagen con el mapa del mundo"<<endl;
        cout<<"3.-Directorio con las banderas"<<endl;
        cout<<"4.-Fichero con el almacen de rutas"<<endl;
        cout<<"5.- Nombre de la imagen con el avion"<<endl;
        cout<<"6.- Nombre de la imagen de la mascara del avion"<<endl;
        cout<<"7.- Nombre de la imagen de salida"<<endl; 

      return 0;
    }
    
    Mundo mundo(argv[1]);
    
    /**********************************************************/
    // Leemos la imagen.
    Imagen mapamundi;
    mapamundi.LeerImagen(argv[2]);
    
    /**********************************************************/
    // Leemos el avión.
    Imagen avion;
    avion.LeerImagen(argv[5],argv[6]);
    
    /**********************************************************/
    // Cargamos el almacén desde el fichero.
    Almacen almacen_rutas(argv[4]);
    
    cout << almacen_rutas << endl;
    
    /**********************************************************/
    // Pedimos al usuario una ruta y la mostramos en pantalla.
    string id_ruta;
    
    cout << "Escoge una ruta: ";
    cin >> id_ruta;
    
    cout << id_ruta << " ";
    Ruta r = almacen_rutas[id_ruta];
    
    for(ruta_cit cit = r.cbegin(); cit != r.cend(); ++cit)
    {
        cout << (*(mundo.find((*cit)))).GetPais() << " ";
    }
    
    cout << endl;
    
    /**********************************************************/
    // Dibujar en el mapamundi la ruta. Primero pintamos sobre
    // los paises por lo que pasamos y luego sobre los puntos medios.
    
    for(int i = 0; i < r.size(); ++i)
    {
        Pais pais = (*(mundo.find(r.at(i))));
        int f, c;
        
        string cad_bandera = argv[3];
        cad_bandera = cad_bandera + "/" + pais.GetBandera();
        Imagen bandera;
        bandera.LeerImagen(cad_bandera.c_str());
        
        f = (mapamundi.num_filas()/180)*(90-r.at(i).GetLat());
        c = (mapamundi.num_cols()/360)*(180+r.at(i).GetLong());
        
        mapamundi.PutImagen(f,c,bandera,OPACO);
    }
    
    for(int i = 0; i < r.size()-1; ++i)
    {
        Pais pais = (*(mundo.find(r.at(i))));
        int f1, f2, c1, c2;
        
        f1 = (mapamundi.num_filas()/180)*(90-r.at(i).GetLat());
        c1 = (mapamundi.num_cols()/360)*(180+r.at(i).GetLong());
        
        f2 = (mapamundi.num_filas()/180)*(90-r.at(i+1).GetLat());
        c2 = (mapamundi.num_cols()/360)*(180+r.at(i+1).GetLong());
        
        Pintar(f1,f2,c1,c2,mapamundi,avion,fabs(f2-f1),fabs(c2-c1));
        
    }
    
    mapamundi.EscribirImagen(argv[7]);
    
    return 0;
}

