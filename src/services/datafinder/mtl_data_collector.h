#ifndef MTL_DATA_COLLECTOR_H
#define MTL_DATA_COLLECTOR_H
#include <string>
#include <iostream>
#include <stdio.h>
#include "./src/services/datafinder/coordinates/coordinatestable.h"
#include "./src/services/datafinder/radiances/scene_rad_data.h"
#include "./src/t_regex/t_regex.h"

#define COOR_LINE 22
#define COORS_NUM 8
#define RAD_LINE 102

using namespace std;
//La clase permite obtener información específica de los archivos MTL
class MTL_Data_Collector
{
public:
    MTL_Data_Collector(int ID);
    //Abre el archivo MTL, permite controlar en caso de que no se logre abrir
    bool OpenMTLFile(string MTL_path);
    //Obtiene y almacena la data del MTL para su posterior uso
    void ObtainData();
    //Devuelve un apuntador a los datos sobre radiancia
    Scene_Rad_Data* GetRadData();
    //Regresa la fecha de obtención de la escena
    string GetDate();
    //Regresa el ángulo del sol con respecto a la tierra
    double GetAzimuth();
private:
    /*Métdodos privados*/
    //Obtiene el valor almacenado en una línea del MTL
    double GetLineValue(string input);
    /*Propiedades del objeto*/
    //Identificador del MTL (Quizá no se esté usando para nada)
    int MTL_ID;
    //El apuntador al archivo MTL
    FILE* mtl_file;
    //La tabla de coordenadas donde se almacenarán las mismas
    CoordinatesTable coors_table;
    //La tabla de radiancias, para más información consultar la clase Scene_Rad_Data
    Scene_Rad_Data radiancesData;
    //Fecha de obtención de la escena
    string date;
    //Ángulo del sol con respecto a la tierra
    double azimuth;
};

#endif // MTL_DATA_COLLECTOR_H
