#ifndef SCENEPROCESSOR_H
#define SCENEPROCESSOR_H

#include <QtCore>
#include <opencv2/opencv.hpp>
#include "areaprocesor.h"
#include "bandscontainer.h"
#include "../../relations/scenedatarelations.h"
#include "../../calculator/filters/ndvi_filter.h"
#include "../../calculator/filters/pm10filter.h"
#include "../../services/datafinder/mtl_data_collector.h"


using namespace cv;
/*La clase se encarga de obtener los datos relacionados con la escena*/
//Actualmente sólo es capaz de obtener la data del MTL pero está pensada para adquirir información del procesamiento de las bandas
class SceneProcessor: public QThread
{
public:
    //El constructor recive el path de origen de la escena así como el nombre de la misma
    SceneProcessor(string origin_path, string scene_name, vector<AreaObjetivo> targets, MTL_Data_Collector collector, bool isL8);
    int contadorAuxiliar;
    //Devuelve el apuntador al colector con la información
private:
    /*Métodos privados*/
    void run();
    void CreateTargetObject(AreaObjetivo* target);
    void TargetsMining(vector<AreaObjetivo> *Targets, BoundingBox *container_bounds);
    /*Atributos privados*/
    string origin_path;
    string scene_name;
    vector<AreaProcesor*> target_miners;
    vector<AreaObjetivo> targets;
    BandsContainer *scene_bands;
    MTL_Data_Collector collector;
};

#endif // SCENEPROCESSOR_H
