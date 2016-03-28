#ifndef MTL_DATA_COLLECTOR_H
#define MTL_DATA_COLLECTOR_H
#include <string>
#include <iostream>
#include <stdio.h>
#include "./include/services/datafinder/coordinates/coordinatestable.h"
#include "./include/services/datafinder/radiances/scene_rad_data.h"
#include "./include/t_regex/t_regex.h"

#define COOR_LINE 22
#define COORS_NUM 8
#define RAD_LINE 102

using namespace std;

class MTL_Data_Collector
{
public:
    MTL_Data_Collector(int ID);
    //Abre el archivo MTL, permite controlar en caso de que no se logre abrir
    bool OpenMTLFile(string MTL_path);
    //Obtiene y almacena la data del MTL para su posterior uso
    void ObtainData();
private:
    /*Métdodos privados*/
    //Obtiene el valor almacenado en una línea del MTL
    double GetLineValue(string input);
    /*Propiedades del objeto*/
    int MTL_ID;
    FILE* mtl_file;
    CoordinatesTable coors_table;
    Scene_Rad_Data radiancesData;
};

#endif // MTL_DATA_COLLECTOR_H
