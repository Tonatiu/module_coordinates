#include "search_save_services.h"

Search_Save_Services::Search_Save_Services()
{
    this->scene_path_queue = pathQueue();
}
//Permite buscar directorios que contienen escenas en el path especificado
bool Search_Save_Services::SearchScenesService(std::string path){
    FILE* stream;
    char buffer[512];
    //Obtención de los resultados arrojados por ls
    stream = this->SearchService(path, "\"[A-Z]{2}[0-9]{14}[A-Z]{3}[0-9]{2}\"");
    //verifica que stream no regrese vacío
    if(stream == NULL)
        return false;
    //Obtiene uno a uno los resultados del stream, cada resultado es un directorio diferente
    while(fgets(buffer, sizeof(buffer), stream)){
        std::string result(buffer);
        //Elimina el salto de linea obtenido por ls
        result.erase(std::remove(result.begin(), result.end(), '\n'), result.end());
        //Se concatena el path padre al nombre del directorio
        std::string full_path = path + "/" + result;
        //Almacenamiento de los paths de las escenas para su posterior uso
        this->scene_path_queue.enqueue(full_path.c_str());
    }

    pclose(stream);
    //Verifica que se hayan obtenido escenas
    if(this->scene_path_queue.getLength() > 0)
        return true;
    return false;
}
//Permite copiar lo almacenado en scene_path_queue al destino especificado por destiny_path
bool Search_Save_Services::CopyService(std::string destiny_path){
    int copyCheck = 0;
    //Inicialización del comando para copiar
    std::string command = "cp -r ";
    //Copiado de los elementos en scene_path_queue
    for(int i = 0; i < this->scene_path_queue.getLength(); i++){
        std::string copy = command + this->scene_path_queue.getNext() + " " + destiny_path;
        const char* command = copy.c_str();
        int copyCheck = system(command);
        //Si algun elemento no se puede copiar por alguna razón devuelve false
        if(copyCheck != 0)
            return false;
    }
    //Regresa true si todos los copiados fueron exitosos
    return true;
}
//Permite realizar comprovaciones de expresiones regulares
bool Search_Save_Services::matches(std::string input, std::string reg_ex){
    regex_t re;

    if(regcomp(&re, reg_ex.c_str(), REG_EXTENDED) != 0)
        return false;

    if(regexec(&re, input.c_str(), (size_t)0, NULL, 0) == 0){
        regfree(&re);
        return true;
    }
    regfree(&re);
    return false;
}
//Busca en path objetos que concuerdan con reg_ex por medio del comando ls y regresa un apuntador a FILE
FILE *Search_Save_Services::SearchService(std::string path, std::string reg_ex){
    std::string command = "ls " + path +" | egrep " + reg_ex;
    //Regreso del resultado de la consulta de ls
    return popen(command.c_str(), "r");
}
//Obtiene las coordenadas de todas las escenas encontradas por SearchScenesService, las cuales están almacenadas en scene_path_queue
void Search_Save_Services::getScenesCoordinates(){
    FILE* stream;
    char buffer[512];
    //Creación de la tabla de coordenadas de acuerdo al número de escenas encontradas
    this->coors_table = (Scene_Coors*) malloc(sizeof(Scene_Coors) * this->scene_path_queue.getLength());
    //Obtención de las coordenadas desde los MTL
    for(int i = 0; i < this->scene_path_queue.getLength(); i++){
        std::string MTL_path = this->scene_path_queue.getNext();
        stream = this->SearchService(MTL_path, ".*_MTL");
        fgets(buffer, sizeof(buffer), stream);
        MTL_path += buffer;
        this->getMTLCoors(MTL_path, i);
    }

}
//Permite obtener las coordenadas de un MTL específicado por MTL_path y las almacena en coors_table en la poscición MTL_ID
void Search_Save_Services::getMTLCoors(std::string MTL_path, int MTL_ID){
    FILE* MTL_File;
    int c = 0;
    char buffer[150];
    std::string line;
    std::string coor_regex = "CORNER_([A-Z]{2})_(LAT|LON)_PRODUCT";
    //Apertura del archivo MTL
    MTL_File = fopen(MTL_path.c_str(), "r");
    //Verificación del archivo
    if(MTL_File == NULL)
        return;

    //Busca la primera concordancia de las coordenadas
    do{
        fgets(buffer, 150, MTL_File);
        line = buffer;
    }while(!this->matches(line, coor_regex));
    //Busca el resto de las concordancias almacenando los valores en un arreglo
    do{
        line = line.substr(0, line.length() - 1);
        std::size_t pos = line.find("=") + 2;
        line = line.substr(pos);
        this->coors_table[MTL_ID].coordinates[c++] = atof(line.c_str());
        fgets(buffer, 150, MTL_File);
        line = buffer;
    }while(this->matches(line, coor_regex));

}

bool Search_Save_Services::QueueisEmpty(){
    return this->scene_path_queue.getLength() == 0;
}

int Search_Save_Services::getQueueLength(){
    return this->scene_path_queue.getLength();
}
