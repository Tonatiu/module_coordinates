#include "processingthread.h"

ProcessingThread::ProcessingThread(pathQueue *scene_path_queue, string origin_path)
{
    this->scene_path_queue = scene_path_queue;
    this->origin_path = origin_path;
    //Creación de los múltiples hilos que obtendrán información de las escenas
    int scenes_num = scene_path_queue->getLength();
    this->mining_threads = (SceneProcessor**) malloc(sizeof(SceneProcessor*) * scenes_num);
}

void ProcessingThread::ScenesMining(){
    int num_scenes = this->scene_path_queue->getLength();
    //Verifica que la cola no esté vacía
    if(num_scenes <= 0)
        return;
    //Inicializa a atodos los hilos que extraerán información de las escenas
    for(int i = 0; i < num_scenes; i++){
        string scene_name = this->scene_path_queue->dequeue();
        this->mining_threads[i] = new SceneProcessor(this->origin_path, scene_name);
        this->mining_threads[i]->start();
    }
}

MTL_Data_Collector *ProcessingThread::GetCollectorFrom(int pos){
    return this->mining_threads[pos]->GetCollector();
}

void ProcessingThread::run(){
    this->ScenesMining();
}
