#include "copy_service.h"

Copy_Service::Copy_Service(pathQueue *queue, string destiny_path, string origin_path)
{
    this->scene_path_queue = queue;
    this->Destiny_Path = destiny_path;
    this->Origin_Path = origin_path;
}

//Permite copiar lo almacenado en scene_path_queue al destino especificado por destiny_path
bool Copy_Service::CopyTo(string file_name){
    string origin;
    //Inicialización del comando para copiar
    string command = "cp -r ";
    //Se concatena el path de origen con el nombre de la escena (la carpeta que la contiene)
    origin = this->Origin_Path + file_name;
    string copy = command + origin + " " + this->Destiny_Path;
    //Copia la carpeta de origen al destino especificado
    //Se retorna false si hubo un error
    return (system(copy.c_str()) != -1);
}

void Copy_Service::run(){
    int num_scenes = this->scene_path_queue->getLength();
    if(num_scenes <= 0)
        return;
    for(int i = 0; (i < num_scenes) && this->running; i++){
        if(this->running){
            //Comprueba que todos los elementos se hayan copiado de forma correcta, en caso contrario el status será false
            this->copy_status &= this->CopyTo(this->scene_path_queue->getNext());
        }
    }
}

bool Copy_Service::GetStatus(){
    return this->copy_status;
}

void Copy_Service::stop_service(){
    this->running = false;
}
