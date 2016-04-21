#ifndef MTL_DATA_COLLECTOR_H
#define MTL_DATA_COLLECTOR_H

#include <iostream>
#include <stdio.h>
#include "./src/services/datafinder/coordinates/coordinatestable.h"
#include "./src/services/datafinder/radiances/scene_rad_data.h"
#include "./src/t_regex/t_regex.h"
#include "mtl_header_regex.h"

#define COOR_LINE 22
#define COORS_NUM 8
#define RAD_LINE 102

using namespace std;
//La clase permite obtener información específica de los archivos MTL
class MTL_Data_Collector
{
public:
    MTL_Data_Collector();
    //Abre el archivo MTL, permite controlar en caso de que no se logre abrir
    bool OpenMTLFile(string MTL_path);
    //Obtiene y almacena la data del MTL para su posterior uso
    void ObtainData();
    //Devuelve un apuntador a los datos sobre radiancia
    Scene_Rad_Data* GetRadData();
    //Regresa la tabla de coordenadas de la escena
    CoordinatesTable* GetCoordinatesTable();
    //Devuelve el nombre de la escena
    string GetSceneID();
    //Regresa el tipo de satélite encotrado
    string GetSpaceCraft();
    //Regresa la fecha de obtención de la escena
    string GetAquiredDate();
    //Obtiene la fecha de creación del archivo
    string GetFileDate();
    //Regresa el ángulo del sol con respecto a la tierra
    double GetAzimuth();
    //Regresa la calidad de la escena
    double GetQuality();
    //Regresa la nubosidad de la escena
    double GetCloudCover();
    //Regresa el tipo de escena
    string GetDataType();
    //Regresa un vector de coordenadas
    vector<Coords> GetCoors();
    //Regresa el string con los datos capturados
    string To_String();
private:
    /*Métdodos privados*/
    //Obtienen el valor almacenado en una línea del MTL
    double LineValue_double(string input);
    string LineValue_string(string input);
    int LineValue_integer(string input);
    /*Propiedades del objeto*/
    //El apuntador al archivo MTL
    FILE* mtl_file;
    /*---------------------------Información adquirida del MTL------------------------------------*/
    //Nombre de la escena satelital
    string SCENE_NAME;
    //Identificador del tipo de satélite (Landsat 4, 7, 8)
    string SPACE_CRAFT_ID;
    //Fecha de obtención de la escena
    string AQUISITION_DATE;
    //Fecha de generacion de la escena
    string FILE_DATE;
    //Ángulo del sol con respecto a la tierra
    double AZIMUT;
    //Calidad de la escena satelital
    double IMG_QUALITY;
    //Nubosidad
    double CLOUD_COVER;
    //Tipo de escena (Para saber si está rectificada)
    string DATA_TYPE;
    /*-------------------------------------------------------------------------------------------*/
    //La tabla de coordenadas donde se almacenarán las mismas
    CoordinatesTable coors_table;
    //La tabla de radiancias, para más información consultar la clase Scene_Rad_Data
    Scene_Rad_Data radiancesData;

};

#endif // MTL_DATA_COLLECTOR_H
