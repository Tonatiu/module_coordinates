#include <iostream>

#ifndef _GEOGRAPHIC_COORDS_H_
    #define _GEOGRAPHIC_COORDS_H_
	/*La clase almacena un punto de coordenadas lat, lng*/
    class Coords{
        double lat, lng;
        
        public:
			//Constructores de clase
            Coords(){}
            Coords(double, double);
			/*Seters y getters*/
            void setLat(double);
            void setLng(double);
            double getLat();
            double getLng();
			//Permite imprimir el contenido de la clase
            void print();
    };

#endif
