#ifndef COORDINATESTABLE_H
#define COORDINATESTABLE_H

#include <string>
#include <string.h>
#include <iostream>
#include <vector>
#include "../../../postgis/geographic/Coords.h"

using namespace std;
//La clase permite almacenar las coordenadas de un archivo MTL
class CoordinatesTable
{
public:
    CoordinatesTable();
    //Añade una coordenada en la posición pos
    void Add_Coordinate(int pos, double value);
    //Regresa el apintador a las coordenadas obtenidas
    double* Get_Coordinates();
    //Permite imprimir el contenido de la clase
    void PrintData();
    //Convierte al arreglo coordinates en un objeto array
    vector<Coords> ArrayToVector();
private:
    //Arreglo de coordenadas
    double coordinates[8];
};

#endif // COORDINATESTABLE_H
