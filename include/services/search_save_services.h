#ifndef SEARCH_SAVE_SERVICES_H
#define SEARCH_SAVE_SERVICES_H
#include "./include/services/queue/pathqueue.h"
#include "./include/services/datafinder/mtl_data_collector.h"

using namespace std;

class Search_Save_Services
{
public:
    Search_Save_Services();
    //Permite buscar las carpetas que contienen las escenas satelitales
    bool SearchScenesService(string path);
    //Permite realizar el copiado de las escenas encontradas por el método anterior a una ubicación
    //definida por destiny_path
    bool CopyService(string destiny_path);
    //Obtiene los datos de las escenas satelitales para su posterior uso
    void GetDataService();
    //Permite conocer el número actual de elementos en la cola de paths
    int getQueueLength();
    //Permite saber si la cola está vacía
    bool QueueisEmpty();
private:
    //Métodos privados
    //Busca en path los directorios o archivos que concuerden con reg_ex
    FILE* SearchService(string path, string reg_ex);
    //Atributos
    pathQueue scene_path_queue;
    string Origin_Path;
    string Destny_Path;
    //Arreglo de data extraída del MTL
    MTL_Data_Collector** dataCollectors;
};

#endif // SEARCH_SAVE_SERVICES_H
