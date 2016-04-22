#include "copy_service.h"

Copy_Service::Copy_Service(vector<string> *queue, string destiny_path, string origin_path)
{
    this->scene_path_queue = queue;
    this->Destiny_Path = destiny_path;
    this->Origin_Path = origin_path;
}

void Copy_Service::run(){
    if(scene_path_queue->empty())
        return;
    for(int i = 0; (i < scene_path_queue->size()) && this->running; i++){
        string filename = (*this->scene_path_queue)[i];
        CopyThread *copy_thread = new CopyThread(this->Origin_Path, this->Destiny_Path, filename);
        copy_thread->start();
        copy_thread->wait();
    }
}

bool Copy_Service::GetStatus(){
    return this->copy_status;
}

void Copy_Service::stop_service(){
    this->running = false;
}
