#ifndef SCENEPROCESSOR_H
#define SCENEPROCESSOR_H

#include <QtCore>
#include "../../services/datafinder/mtl_data_collector.h"

/*La clase se encarga de obtener los datos relacionados con la escena*/
//Actualmente sólo es capaz de obtener la data del MTL pero está pensada para adquirir información del procesamiento de las bandas
class SceneProcessor: public QThread
{
public:
    //El constructor recive el path de origen de la escena así como el nombre de la misma
    SceneProcessor(string origin_path, string scene_name);
    //Devuelve el apuntador al colector con la información
    MTL_Data_Collector *GetCollector();
private:
    /*Métodos privados*/
    void run();
    //Obtiene la data del MTL
    void GetMTLData();
    /*Atributos privados*/
    string origin_path;
    string scene_name;
    MTL_Data_Collector *collector;
};

#endif // SCENEPROCESSOR_H
