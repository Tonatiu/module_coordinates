#ifndef SCENEPROCESSOR_H
#define SCENEPROCESSOR_H

#include <QtCore>
#include <opencv2/opencv.hpp>
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
    SceneProcessor(string origin_path, string scene_name, SceneDataRelations *relations);
    //Devuelve el apuntador al colector con la información
private:
    /*Métodos privados*/
    void run();
    //Abre la banda de una escena
    Mat OpenBand(int band);
    //
    void AplyEnviromentalFilters();
    /*Atributos privados*/
    string origin_path;
    string scene_name;
    SceneDataRelations* relations;
};

#endif // SCENEPROCESSOR_H
