#include "search_save_services.h"

using namespace std;

Search_Save_Services::Search_Save_Services()
{
    this->scene_path_queue = pathQueue();
}
//Permite buscar directorios que contienen escenas en el path especificado
bool Search_Save_Services::SearchScenesService(string path){
    FILE* stream;
    char buffer[512];
    this->Origin_Path = path + "/";
    //Obtención de los resultados arrojados por ls
    stream = this->SearchService(path, "\"[A-Z]{2}[0-9]{14}[A-Z]{3}[0-9]{2}\"");
    //verifica que stream no regrese vacío
    if(stream == NULL)
        return false;
    //Obtiene uno a uno los resultados del stream, cada resultado es un directorio diferente
    while(fgets(buffer, sizeof(buffer), stream)){
        string result(buffer);
        //Elimina el salto de linea obtenido por ls
        result.erase(remove(result.begin(), result.end(), '\n'), result.end());
        //Almacenamiento de los paths de las escenas para su posterior uso
        this->scene_path_queue.enqueue(result.c_str());
    }

    pclose(stream);
    //Verifica que se hayan obtenido escenas
    int queuelength = this->scene_path_queue.getLength();
    if(queuelength > 0){
        return true;
    }

    return false;
}
//Permite copiar lo almacenado en scene_path_queue al destino especificado por destiny_path
bool Search_Save_Services::CopyService(string destiny_path){
    int queueLength = this->scene_path_queue.getLength();
    this->Destny_Path = destiny_path;
    string origin;
    //Inicialización del comando para copiar
    string command = "cp -r ";
    //Copiado de los elementos en scene_path_queue
    for(int i = 0; i < queueLength; i++){
        //Se concatena el path de origen con el nombre de la escena (la carpeta que la contiene)
        origin = this->Origin_Path + this->scene_path_queue.getNext();
        string copy = command + origin + " " + destiny_path;
        //Copia la carpeta de origen al destino especificado
        int copyCheck = system(copy.c_str());
        //Si algun elemento no se puede copiar por alguna razón devuelve false
        if(copyCheck != 0)
            return false;
    }
    //Regresa true si todos los copiados fueron exitosos
    return true;
}

//Busca en path objetos que concuerdan con reg_ex por medio del comando ls y regresa un apuntador a FILE
FILE *Search_Save_Services::SearchService(string path, string reg_ex){
    string command = "ls " + path +" | egrep " + reg_ex;
    //Regreso del resultado de la consulta de ls
    return popen(command.c_str(), "r");
}

void Search_Save_Services::GetDataService(){
    int scenesCounter = this->scene_path_queue.getLength();
    if(scenesCounter <= 0)
        return;

    this->dataCollectors = (MTL_Data_Collector *) malloc(sizeof(MTL_Data_Collector) * scenesCounter);

    for(int i = 0; i < scenesCounter; i++){
        this->dataCollectors[i] = MTL_Data_Collector(i);
        string sceneName = this->scene_path_queue.getNext();
        string MTL_path = this->Origin_Path + "/" + sceneName + "/" + sceneName + "_MTL.txt";
        if(this->dataCollectors[i].OpenMTLFile(MTL_path)){
            this->dataCollectors[i].ObtainData();
        }
    }
}

bool Search_Save_Services::QueueisEmpty(){
    return this->scene_path_queue.getLength() <= 0;
}

int Search_Save_Services::getQueueLength(){
    return this->scene_path_queue.getLength();
}
