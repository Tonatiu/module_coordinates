#include "sceneprocessor.h"

SceneProcessor::SceneProcessor(string origin_path, string scene_name, SceneDataRelations *relations)
{
    this->origin_path = origin_path;
    this->scene_name = scene_name;
    this->relations = relations;
}

Mat SceneProcessor::OpenBand(int band){
    string band_path = this->origin_path + this->scene_name + "/" + this->scene_name + "_B" + to_string(band) + ".TIF";
    return imread(band_path);
}


void SceneProcessor::AplyEnviromentalFilters(){
    PM10Filter filterpm10;
    NDVI_Filter filterndvi;
    double PM10_prom, ndvi_prom;



}

void SceneProcessor::run(){

}
