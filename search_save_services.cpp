#include "search_save_services.h"

Search_Save_Services::Search_Save_Services()
{
    this->scene_path_queue = pathQueue();
    this->coors_table = CoordinatesTable();
}
//Permite buscar directorios que contienen escenas en el path especificado
bool Search_Save_Services::SearchScenesService(std::string path){
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
        std::string result(buffer);
        //Elimina el salto de linea obtenido por ls
        result.erase(std::remove(result.begin(), result.end(), '\n'), result.end());
        //Almacenamiento de los paths de las escenas para su posterior uso
        this->scene_path_queue.enqueue(result.c_str());
    }

    pclose(stream);
    //Verifica que se hayan obtenido escenas
    int queuelength = this->scene_path_queue.getLength();
    if(queuelength > 0){
        this->coors_table.createTable(queuelength);
        return true;
    }

    return false;
}
//Permite copiar lo almacenado en scene_path_queue al destino especificado por destiny_path
bool Search_Save_Services::CopyService(std::string destiny_path){
    int queueLength = this->scene_path_queue.getLength();
    this->Destny_Path = destiny_path;
    std::string origin;
    //Inicialización del comando para copiar
    std::string command = "cp -r ";
    //Copiado de los elementos en scene_path_queue
    for(int i = 0; i < queueLength; i++){
        //Se concatena el path de origen con el nombre de la escena (la carpeta que la contiene)
        origin = this->Origin_Path + this->scene_path_queue.getNext();
        std::string copy = command + origin + " " + destiny_path;
        //Copia la carpeta de origen al destino especificado
        int copyCheck = system(copy.c_str());
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
    //Obtiene el número de escenas previamente encontradas
    int Num_Scenes = this->scene_path_queue.getLength();
    for(int i = 0; i < Num_Scenes; i++){
        //Obtención y almacenamiento del nombre de la escena en la estructura Scene_Coors
        std::string sceneName = this->scene_path_queue.getNext();
        this->coors_table.addCellName(i, sceneName);
        //Envío del path completo para su procesamiento
        std::string MTL_path = this->Destny_Path + "/" + sceneName + "/" + sceneName + "_MTL.txt";
        this->getMTLCoors(MTL_path, i);
    }
    this->coors_table.printTable();
}
//Permite obtener las coordenadas de un MTL específicado por MTL_path y las almacena en coors_table en la poscición MTL_ID
void Search_Save_Services::getMTLCoors(std::string MTL_path, int MTL_ID){
    FILE* MTL_file;
    int c = 0;
    //Expresión regular para encontrar las lineas correspondientes a las coordenadas
    std::string coor_regx = "CORNER_([A-Z]{2})_(LAT|LON)_PRODUCT";
    std::string line;
    std::string value;
    char buffer[150];
    //Verifica que exista el path
    if(MTL_path.length() < 1){
        std::cout << "Warning: Not mainpath found\n";
        return;
    }
    //Abre el archivo MTL
    MTL_file = fopen(MTL_path.c_str(), "r");
    if(MTL_file == NULL){
        std::cout << "Error: Could not open the file\n";
    }
    //Busca la primera concordancia de las coordenadas
    do{
        fgets(buffer, 150, MTL_file);
        line = buffer;
    }while(!this->matches(line, coor_regx));
    //Busca el resto de las concordancias almacenando los valores en un arreglo
    do{
        line = line.substr(0, line.length() - 1);
        std::size_t pos = line.find("=") + 2;
        line = line.substr(pos);
        this->coors_table.addValue(MTL_ID, c, atof(line.c_str()));
        c++;
        fgets(buffer, 150, MTL_file);
        line = buffer;
    }while(this->matches(line, coor_regx));
}

bool Search_Save_Services::QueueisEmpty(){
    return this->scene_path_queue.getLength() <= 0;
}

int Search_Save_Services::getQueueLength(){
    return this->scene_path_queue.getLength();
}
