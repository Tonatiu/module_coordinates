#ifndef SCENEDATARELATIONS_H
#define SCENEDATARELATIONS_H

#include "../services/datafinder/mtl_data_collector.h"
#include "../postgis/postgis/entity/AreaObjetivo.h"
#include <vector>
#include <string>

/*Esta clase alamacena la información relativa a las escenas. Todos los datos se relacionan entre si*/
class SceneDataRelations
{
public:
    SceneDataRelations();
    //Regresa la cantidad de escenas almacenadas
    int GetFilesCount();
    //Indica si no hay escenas en la estructura
    bool FileNamesEmpty();
    //Devuelve un apuntador a los nombres de las escenas
    vector<string>* GetFileNames();
    //Regresa el nombre de una escena almacenado en la posición id
    string GetFileNameByID(int id);
    //Borra el nombre de escena de la posición id
    void EraseFileByID(int id);
    //Inserta un colector en la colección de colectores
    void PushCollector(MTL_Data_Collector collector);
    //Inserta un nombre de escena en la colección correspondiente
    void PushSceneName(string value);
    //Inserta un vector de targets
    void PushSceneTargets(vector<AreaObjetivo> targets);
private:
    /*Colecciones de datos de las escenas*/
    vector<MTL_Data_Collector> collectors;
    vector<vector<AreaObjetivo>> scene_targets;
    vector<string> file_names;
};

#endif // SCENEDATARELATIONS_H
