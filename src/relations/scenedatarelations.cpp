#include "scenedatarelations.h"

SceneDataRelations::SceneDataRelations()
{

}

int SceneDataRelations::GetFilesCount(){
    return this->file_names.size();
}

bool SceneDataRelations::FileNamesEmpty(){
    return this->file_names.empty();
}

vector<string>* SceneDataRelations::GetFileNames(){
    return &this->file_names;
}

string SceneDataRelations::GetFileNameByID(int id){
    return this->file_names[id];
}

void SceneDataRelations::EraseFileByID(int id){
    this->file_names.erase(file_names.begin() + id);
}

void SceneDataRelations::PushCollector(MTL_Data_Collector collector){
    this->collectors.push_back(collector);
}

void SceneDataRelations::PushSceneName(string value){
    this->file_names.push_back(value);
}

void SceneDataRelations::PushSceneTargets(vector<AreaObjetivo> targets){
    this->scene_targets.push_back(targets);
}
