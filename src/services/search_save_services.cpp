#include "search_save_services.h"

using namespace std;

Search_Save_Services::Search_Save_Services()
{
}
//Permite buscar directorios que contienen escenas en el path especificado
bool Search_Save_Services::SearchScenesService(string path, SceneDataRelations *scene_data_relations){
    FILE* stream;
    char buffer[512];
    this->Origin_Path = path + "/";
    //Obtención de los resultados arrojados por ls
    stream = this->SearchService(path, SCENE_NAME);
    //verifica que stream no regrese vacío
    if(stream == NULL)
        return false;
    //Obtiene uno a uno los resultados del stream, cada resultado es un directorio diferente
    while(fgets(buffer, sizeof(buffer), stream)){
        string result(buffer);
        //Elimina el salto de linea obtenido por ls
        result.erase(remove(result.begin(), result.end(), '\n'), result.end());
        //Almacenamiento de los paths de las escenas para su posterior uso
        scene_data_relations->PushSceneName(result);
    }

    pclose(stream);
    //Verifica que se hayan obtenido escenas
    int queuelength = scene_data_relations->GetFilesCount();
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

string Search_Save_Services::GetOriginPath(){
    return this->Origin_Path;
}
