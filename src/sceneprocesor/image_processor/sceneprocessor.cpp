#include "sceneprocessor.h"

SceneProcessor::SceneProcessor(string origin_path, string scene_name, vector<AreaObjetivo> targets, MTL_Data_Collector collector, bool isL8)
{
    this->origin_path = origin_path;
    this->scene_name = scene_name;
    this->targets = targets;
    this->collector = collector;
    this->scene_bands = new BandsContainer(isL8);
    this->filter_pm10 = new PM10Filter(&collector);
    this->filter_ndvi = new NDVI_Filter(&collector);
}

void SceneProcessor::run(){
    int num_targets = this->targets.size();
    this->scene_bands->OpenBands(this->origin_path, this->scene_name);
    //Generación de coordenadas del contenedor
    BoundingBox container_bounds(this->collector.GetCoors());
    for(int i = 0; i < num_targets; i++){
        //Adquisición de un área objetivo
        AreaObjetivo target = targets.back();
        targets.pop_back();
        //Inserción de los datos provenientes del MTL
        target.setId(this->collector.GetSceneID());
        target.setDateAcquired(collector.GetAquiredDate());
        target.setSceneCenterTime(collector.GetFileDate());
        target.setCalidad(collector.GetQuality());
        target.setNubosidad(collector.GetCloudCover());
        //Procesamiento de las bandas en búsqueda de pm10 y ndvi
        AreaProcesor* area_miner = new AreaProcesor(this->scene_bands, target, container_bounds, filter_pm10, filter_ndvi);
        area_miner->start();
    }
}
