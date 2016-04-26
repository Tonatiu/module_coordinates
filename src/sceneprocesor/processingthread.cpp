#include "processingthread.h"

ProcessingThread::ProcessingThread(SceneDataRelations *relations, string origin_path)
{
    this->relations = relations;
    this->origin_path = origin_path;
}

void ProcessingThread::CreateProcess(vector<SceneProcessor*> *procesors){
    string scene_name = relations->GetLastFileName();
    vector<AreaObjetivo> targets = relations->GetLastsTargets();
    MTL_Data_Collector collector = relations->GetLastCollector();
    SceneProcessor* scene_procesor = new SceneProcessor(origin_path, scene_name, targets, collector, collector.IsL8());
    procesors->push_back(scene_procesor);
    scene_procesor->start();
}

void ProcessingThread::run(){
    int num_scenes;
    num_scenes = relations->GetFilesCount();
    vector<SceneProcessor*> procesors;
    //Mientras la lista de escenas no esté vacía
    while(!relations->FileNamesEmpty()){
        //Se generan lotes de 3 hilos para evitar que se devore toda la memoria abriendo las imágenes .TIF
        if(num_scenes >= 3){
            for(int i = 0; i < 3; i++){
                this->CreateProcess(&procesors);
            }
            for(int i = 0; i < 3; i++){
                SceneProcessor *process = procesors.back();
                if(process->isRunning())
                    process->wait();
                procesors.pop_back();
            }
        }
        else{
            for(int i = 0; i < num_scenes; i++){
                this->CreateProcess(&procesors);
            }
            for(int i = 0; i < num_scenes; i++){
                SceneProcessor *process = procesors.back();
                if(process->isRunning())
                    process->wait();
                procesors.pop_back();
            }
        }
    }
}
