#include "sceneprocessor.h"

SceneProcessor::SceneProcessor(string origin_path, string scene_name, vector<AreaObjetivo> targets, MTL_Data_Collector collector, bool isL8)
{
    this->origin_path = origin_path;
    this->scene_name = scene_name;
    this->targets = targets;
    this->collector = collector;
    this->scene_bands = new BandsContainer(isL8);
}

void SceneProcessor::CreateTargetObject(AreaObjetivo *target){
    //Inserción de los datos provenientes del MTL
    target->setId(this->collector.GetSceneID());
    target->setDateAcquired(this->collector.GetAquiredDate());
    target->setSceneCenterTime(this->collector.GetFileDate());
    target->setCalidad(this->collector.GetQuality());
    target->setNubosidad(this->collector.GetCloudCover());
}

void SceneProcessor::run(){
    this->scene_bands->OpenBands(this->origin_path, this->scene_name);
    //Generación de coordenadas del contenedor
    BoundingBox container_bounds(this->collector.GetCoors());
    AreaProcesor* area_miner;
    AreaObjetivo target;
    TargetsMining(&this->targets, &container_bounds);
    this->exit();
}

void SceneProcessor::TargetsMining(vector<AreaObjetivo> *Targets, BoundingBox *container_bounds){
    AreaProcesor* area_miner;
    AreaObjetivo target;
    vector<AreaProcesor*> miners;

    if(Targets->size() == 0)
        return;

    if(Targets->size() >= 3){
        for(int i = 0; i < 3; i++){
            target = Targets->back();
            Targets->pop_back();
            CreateTargetObject(&target);
            area_miner = new AreaProcesor(this->scene_bands, target, *container_bounds, &collector);
            miners.push_back(area_miner);
            area_miner->start();
        }
        for(int i = 0; i < 3; i++){
            area_miner = miners.back();
            area_miner->wait();
            miners.pop_back();
        }
    }else if(Targets->size() > 0 && Targets->size() < 3){
        int count = Targets->size();
        for(int i = 0; i < count; i++){
            target = Targets->back();
            Targets->pop_back();
            CreateTargetObject(&target);
            area_miner = new AreaProcesor(this->scene_bands, target, *container_bounds, &collector);
            miners.push_back(area_miner);
            area_miner->start();
        }
        for(int i = 0; i < count; i++){
            area_miner = miners.back();
            area_miner->wait();
            miners.pop_back();
        }
    }
    TargetsMining(Targets, container_bounds);
}


