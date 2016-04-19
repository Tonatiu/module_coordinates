#include "sceneprocessor.h"

SceneProcessor::SceneProcessor(string origin_path, string scene_name)
{
    this->origin_path = origin_path;
    this->scene_name = scene_name;
}

void SceneProcessor::GetMTLData(){
    //Genera un objeto colector
    this->collector = new MTL_Data_Collector();
    string MTL_path = this->origin_path + "/" + this->scene_name + "/" + this->scene_name + "_MTL.txt";

    if(this->collector->OpenMTLFile(MTL_path)){
        this->collector->ObtainData();
    }

}

MTL_Data_Collector *SceneProcessor::GetCollector(){
    return this->collector;
}

void SceneProcessor::run(){
    this->GetMTLData();
}
