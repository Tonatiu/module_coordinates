#ifndef SEARCH_SAVE_SERVICES_H
#define SEARCH_SAVE_SERVICES_H
#include "pathqueue.h"
//Estructura que almacena las coordenadas encontradas en un MTL
//Almacena la coordenadas y el nombre del MTL
typedef struct scene_coordinates{
    double coordinates[8];
    std::string sceneName;
}Scene_Coors;

class Search_Save_Services
{
public:
    Search_Save_Services();
    //Permite buscar las carpetas que contienen las escenas satelitales
    bool SearchScenesService(std::string path);
    //Permite realizar el copiado de las escenas encontradas por el método anterior a una ubicación
    //definida por destiny_path
    bool CopyService(std::string destiny_path);
    //Verifica expresiones regulares
    bool matches(std::string input, std::string reg_ex);
    //Obtiene las coordenandas de las escenas encontradas por SearchScenesService
    void getScenesCoordinates();
    //Permite conocer el número actual de elementos en la cola de paths
    int getQueueLength();
    //Permite saber si la cola está vacía
    bool QueueisEmpty();
private:
    //Métodos privados
    //El método permite obtener las coordenadas de un MTL específico
    void getMTLCoors(std::string MTL_path, int MTL_ID);
    //Busca en path los directorios o archivos que concuerden con reg_ex
    FILE* SearchService(std::string path, std::string reg_ex);
    //Atributos
    pathQueue scene_path_queue;
    //Arreglo de coordenadas
    Scene_Coors* coors_table;
};

#endif // SEARCH_SAVE_SERVICES_H
