#ifndef COORDINATESTABLE_H
#define COORDINATESTABLE_H
#include <string>
#include <string.h>
#include <iostream>

using namespace std;
//Estructura que almacena las coordenadas encontradas en un MTL
//Almacena la coordenadas y el nombre del MTL
typedef struct scene_coordinates{
    double* coordinates;
    char* sceneName;
}Scene_Coors;
//La clase permite almacenar las coordenadas de un archivo MTL
class CoordinatesTable
{
public:
    CoordinatesTable();
    //Permite añadir el nombre de la escena a unregistro de coordenadas
    void addCellName(int position, string sceneName);
    //Permite añadir valores al registro de coordenadas
    void addValue(int cellPos, int position, double value);
    //Permite generar la tabla de coordenadas
    void createTable(int tableSize);
    //Permite imprimir el contenido de la tabla de coordenadas
    void printTable();
private:
    Scene_Coors* CoorsTable;
    int tableSize;
};

#endif // COORDINATESTABLE_H
