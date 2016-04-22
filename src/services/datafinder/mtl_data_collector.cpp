#include "mtl_data_collector.h"

using namespace std;

MTL_Data_Collector::MTL_Data_Collector()
{
    this->mtl_file = NULL;
    this->coors_table = CoordinatesTable();
    this->radiancesData = Scene_Rad_Data();
}

bool MTL_Data_Collector::OpenMTLFile(string MTL_path){
    this->mtl_file = fopen(MTL_path.c_str(), "r");
    if(this->mtl_file == NULL)
        return false;
    return true;
}

void MTL_Data_Collector::ObtainData(){
    char buffer[100];
    string line;
    /*---------------------------*/
    //Existen por que en estos casos hay más de un elemento
    int c_coors = 0;
    int c_add_rad = 0;
    int c_mult_rad = 0;
    /*---------------------------*/
    double value;
    //Lectura del MTL línea por línea
    while(fgets(buffer, sizeof(buffer), this->mtl_file) != NULL){
        line = buffer;
        //Caso en que se localiza una coordenada
        if(matches(line, COORS_REGEX)){
            value = this->LineValue_double(line);
            this->coors_table.Add_Coordinate(c_coors, value);
            c_coors++;
        }
        //Si se localiza un valor de radiancia multiplicativo
        else if(matches(line, RAD_MULT_REGEX)){
            value = this->LineValue_double(line);
            this->radiancesData.Set_Mult_Rad(c_mult_rad, value);
            c_mult_rad++;
        }
        //Si se localiza un valor de radiancia aditivo
        else if(matches(line, RAD_ADD_REGEX)){
            value = this->LineValue_double(line);
            this->radiancesData.Set_Add_Rad(c_add_rad, value);
            c_add_rad++;
        }
        //Caso de localizar una fecha de adquisición
        else if(matches(line, AQUAIRED_DATE_REGEX)){
            this->AQUISITION_DATE = this->LineValue_string(line);
        }
        //En caso de encontrar la inclinación solar
        else if(matches(line, SUN_AZIMUTH_REGEX)){
            this->AZIMUT = this->LineValue_double(line);
        }
        //Se localiza el tipo de satélite que tomo la escena
        else if(matches(line, SPACECRAFT_TYPE_REGEX)){
            this->SPACE_CRAFT_ID = this->LineValue_string(line);
        }
        //En caso de localizar el nombre de la escena
        else if(matches(line, NAME_REGEX)){
            this->SCENE_NAME = this->LineValue_string(line);
        }
        //Si se localiza la calidad de la escena
        else if(matches(line, QUALITY_REGEX)){
            this->IMG_QUALITY = this->LineValue_double(line);
        }
        //Si se localiza la covertura de nubes
        else if(matches(line, CLOUD_COVER_REGEX)){
            this->CLOUD_COVER = this->LineValue_double(line);
        }
        //En caso de encontrar el tipo de escena (L0, L1, L2)
        else if(matches(line, CORRECTION_TYPE_REGEX)){
            this->DATA_TYPE = this->LineValue_string(line);
        }
        //En caso de localizar la fecha de creación del archivo
        else if(matches(line, FILE_DATE_REGEX)){
            this->FILE_DATE = this->LineValue_string(line);
        }
    }
}

/*-----------------------------Getters de la clase------------------------------*/
string MTL_Data_Collector::GetSceneID(){
    return this->SCENE_NAME;
}

string MTL_Data_Collector::GetSpaceCraft(){
    return this->SPACE_CRAFT_ID;
}

string MTL_Data_Collector::GetAquiredDate(){
    return this->AQUISITION_DATE;
}

string MTL_Data_Collector::GetFileDate(){
    return this->FILE_DATE;
}

double MTL_Data_Collector::GetAzimuth(){
    return this->AZIMUT;
}

double MTL_Data_Collector::GetQuality(){
    return this->IMG_QUALITY;
}

double MTL_Data_Collector::GetCloudCover(){
    return this->CLOUD_COVER;
}

string MTL_Data_Collector::GetDataType(){
    return this->DATA_TYPE;
}

Scene_Rad_Data* MTL_Data_Collector::GetRadData(){
    return &this->radiancesData;
}

vector<Coords> MTL_Data_Collector::GetCoors(){
    return this->coors_table.ArrayToVector();
}

bool MTL_Data_Collector::IsL8(){
    return matches(this->DATA_TYPE, IS_L8_REGEX);
}

/*-----------------------------Miscelaneas-------------------------------------*/

double MTL_Data_Collector::LineValue_double(string input){
    string line;
    line = input;
    //Se elimina la secencia \n del final de la línea
    line = line.substr(0, line.length() - 1);
    //Se localiza la igualdad y se apunta al inicio del número
    size_t pos = line.find("=") + 2;
    //Obtención del string que representa al valor
    line = line.substr(pos);
    //Regreso del string a double
    return atof(line.c_str());
}

string MTL_Data_Collector::LineValue_string(string input){
    string line = input;
    //En caso de que el valor esté rodeado por comillas
    if(matches(input, QUOT_VALUE_REGEX)){
        //Eliminación de \n y " del final de la línea
        line = line.substr(0, line.length() - 2);
        //Obtención del valor sin comilla inicial
        size_t pos = line.find("=") + 3;
        line = line.substr(pos);
    }
    //Caso en el que el valor está libre de comillas
    else{
        line = line.substr(0, line.length() - 1);
        size_t pos = line.find("=") + 2;
        line = line.substr(pos);
    }

    return line;
}

int MTL_Data_Collector::LineValue_integer(string input){
    string line;
    line = input;
    line = line.substr(0, line.length() - 1);
    //Se localiza la igualdad y se apunta al inicio del número
    size_t pos = line.find("=") + 2;
    //Obtención del string que representa al valor
    line = line.substr(pos);
    //Regreso del string a double
    return atoi(line.c_str());
}

string MTL_Data_Collector::To_String(){
    return this->SCENE_NAME + "\n" +
           this->SPACE_CRAFT_ID + "\n" +
           this->AQUISITION_DATE + "\n" +
           this->FILE_DATE + "\n" +
           to_string(this->AZIMUT) + "\n" +
           to_string(this->IMG_QUALITY) + "\n" +
           to_string(this->CLOUD_COVER) + "\n" +
           this->DATA_TYPE + "\n";
}
