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


//Busca en path objetos que concuerdan con reg_ex por medio del comando ls y regresa un apuntador a FILE
FILE *Search_Save_Services::SearchService(string path, string reg_ex){
    string command = "ls " + path +" | egrep " + reg_ex;
    //Regreso del resultado de la consulta de ls
    return popen(command.c_str(), "r");
}
//Obtiene ciertos datos del la metadata MTL. dataCollector es quien se encarga de la recopilación
//y almacenamiento
void Search_Save_Services::GetDataService(){
    if(this->QueueisEmpty())
        return;
    //Obtención del número de escenas encontradas
    int scenesCounter = this->scene_path_queue.getLength();
    //creación del arreglo de punteros para los recolectores de datos para cada escena encontrada
    this->dataCollectors = (MTL_Data_Collector **) malloc(sizeof(MTL_Data_Collector*) * scenesCounter);
    if(this->dataCollectors == NULL){
        cout << "Error, Memory out!!\n";
        exit(0);
    }
    //Invocación a  cada recolector para realizar sus tareas
    for(int i = 0; i < scenesCounter; i++){
        this->dataCollectors[i] = new MTL_Data_Collector();
        //Creacipon del path del archivo de metadata
        string sceneName = this->scene_path_queue.getNext();
        string MTL_path = this->Origin_Path + "/" + sceneName + "/" + sceneName + "_MTL.txt";
        //Apertura del archivo, en caso de no abrirse se ignora y se pasa al siguiente
        if(this->dataCollectors[i]->OpenMTLFile(MTL_path)){
            this->dataCollectors[i]->ObtainData();
        }
    }
}
//Verifica si la cola de datos está vacía
bool Search_Save_Services::QueueisEmpty(){
    return this->scene_path_queue.getLength() <= 0;
}
//Obtiene la longitud de la cola
int Search_Save_Services::getQueueLength(){
    return this->scene_path_queue.getLength();
}

string Search_Save_Services::GetOriginPath(){
    return this->Origin_Path;
}

pathQueue* Search_Save_Services::GetQueue(){
    return &this->scene_path_queue;
}
