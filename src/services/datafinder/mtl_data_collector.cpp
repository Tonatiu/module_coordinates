#include "./include/services/datafinder/mtl_data_collector.h"

using namespace std;

MTL_Data_Collector::MTL_Data_Collector(int ID)
{
    this->mtl_file = NULL;
    this->coors_table = CoordinatesTable();
    this->radiancesData = Scene_Rad_Data();
    this->MTL_ID = ID;
}
//El método recibe un path al archivo que se desea abrir, en caso de error se devuelve un false
bool MTL_Data_Collector::OpenMTLFile(string MTL_path){
    this->mtl_file = fopen(MTL_path.c_str(), "r");
    if(this->mtl_file == NULL)
        return false;
    return true;
}
//Obtiene el valor double de una línea obtenida del MTL
double MTL_Data_Collector::GetLineValue(string input){
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
    //Declaración de expresiones regulares
    string CoorsRegex = "CORNER_([A-Z]{2})_(LAT|LON)_PRODUCT";
    string Rad_Mult_Regex = "RADIANCE_MULT_BAND_([0-9]+)";
    string Rad_Add_Regex = "RADIANCE_ADD_BAND_([0-9]+)";
    string Aquaired_Date_regex = "DATE_ACQUIRED";
    string Sun_Azimuth_Regex = "SUN_AZIMUTH";
    //Lectura del MTL línea por línea
    while(fgets(buffer, sizeof(buffer), this->mtl_file) != NULL){
        line = buffer;
        //Caso en que se localisa una coordenada
        if(matches(line, CoorsRegex)){
            value = this->GetLineValue(line);
            this->coors_table.Add_Coordinate(c_coors, value);
            c_coors++;
        }
        //Si se localiza un valor de radiancia multiplicativo
        else if(matches(line, Rad_Mult_Regex)){
            value = this->GetLineValue(line);
            this->radiancesData.Set_Mult_Rad(c_mult_rad, value);
            c_mult_rad++;
        }
        //Si se localiza un valor de radiancia aditivo
        else if(matches(line, Rad_Add_Regex)){
            value = this->GetLineValue(line);
            this->radiancesData.Set_Add_Rad(c_add_rad, value);
            c_add_rad++;
        }
        //Caso de localizar una fecha de adquisición
        else if(matches(line, Aquaired_Date_regex)){
            line = line.substr(0, line.length() - 1);
            size_t pos = line.find("=") + 2;
            line = line.substr(pos);
            this->date = line;
        }
        //En caso de encontrar la inclinación solar
        else if(matches(line, Sun_Azimuth_Regex)){
            this->azimuth = this->GetLineValue(line);
        }
    }
}

double MTL_Data_Collector::GetAzimuth(){
    return this->azimuth;
}

Scene_Rad_Data* MTL_Data_Collector::GetRadData(){
    return &this->radiancesData;
}

string MTL_Data_Collector::GetDate(){
    return this->date;
}
