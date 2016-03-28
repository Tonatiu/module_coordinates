#ifndef COORDINATESTABLE_H
#define COORDINATESTABLE_H
#include <string>
#include <string.h>
#include <iostream>

using namespace std;
//La clase permite almacenar las coordenadas de un archivo MTL
class CoordinatesTable
{
public:
    CoordinatesTable();
    void Add_Coordinate(int pos, double value);
    double* Get_Coordinates();
    void PrintData();
private:
    double coordinates[8];
};

#endif // COORDINATESTABLE_H
