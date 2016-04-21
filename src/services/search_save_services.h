#ifndef SEARCH_SAVE_SERVICES_H
#define SEARCH_SAVE_SERVICES_H

#include "./src/services/datafinder/mtl_data_collector.h"
#include "../relations/scenedatarelations.h"
#include <dirent.h>
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>
#include <stdlib.h>
#include <regex.h>
#include <stdio.h>
#include <algorithm>
#include <string.h>
#include <fstream>

using namespace std;

class Search_Save_Services
{
public:
    Search_Save_Services();
    //Permite buscar las carpetas que contienen las escenas satelitales
    bool SearchScenesService(string path, SceneDataRelations *scene_data_relations);
    //Regresa el path de origen
    string GetOriginPath();
private:
    //Métodos privados
    //Busca en path los directorios o archivos que concuerden con reg_ex
    FILE* SearchService(string path, string reg_ex);
    //Atributos
    string Origin_Path;
    string Destny_Path;
    //Arreglo de data extraída del MTL
    vector<MTL_Data_Collector*> collectors;
    SceneDataRelations *scene_data_relations;
};

#endif // SEARCH_SAVE_SERVICES_H
