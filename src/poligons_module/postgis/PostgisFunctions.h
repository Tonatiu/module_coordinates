#include <iostream>
#include <pqxx/pqxx>
#include <vector>

#include "postgis.h"
#include "../geographic/GeoPolygon.h"
#include "../geographic/GeoPoint.h"
#include "entity/Municipio.h"

using namespace std;
using namespace pqxx;

#ifndef _POSTGIS_POSTGIS_FUNCTIONS_H_
    #define _POSTGIS_POSTGIS_FUNCTIONS_H_
    /*La clase define una serie de funciones que permiten obtener los polígonos obtenidos en un área definida por dos puntos geográficos*/
    
    class PostgisFunctions{
        public:
			/*Regresa un polígono dados dos puntos geográficos*/
            static GeoPolygon getBounds(GeoPoint p1, GeoPoint p2);
			/*Devuelve un vector de todos los municipios encontrados en una escena satelital*/
            static std::vector<Municipio> getMunicipiosContained(GeoPolygon);
            static std::string getTableSrid(std::string, std::string);
    };
#endif
