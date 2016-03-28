#include "./include/services/datafinder/mtl_data_collector.h"

using namespace std;

MTL_Data_Collector::MTL_Data_Collector(int ID)
{
    this->mtl_file = NULL;
    this->coors_table = CoordinatesTable();
    this->radiancesData = Scene_Rad_Data();
    this->MTL_ID = ID;
}

bool MTL_Data_Collector::OpenMTLFile(string MTL_path){
    this->mtl_file = fopen(MTL_path.c_str(), "r");
    if(this->mtl_file == NULL)
        return false;
    return true;
}

double MTL_Data_Collector::GetLineValue(string input){
    string line;
    line = input;

    line = line.substr(0, line.length() - 1);
    size_t pos = line.find("=") + 2;
    line = line.substr(pos);

    return atof(line.c_str());
}

void MTL_Data_Collector::ObtainData(){
    char buffer[100];
    string line;
    int c_coors = 0;
    int c_add_rad = 0;
    int c_mult_rad = 0;
    double value;

    string CoorsRegex = "CORNER_([A-Z]{2})_(LAT|LON)_PRODUCT";
    string Rad_Mult_Regex = "RADIANCE_MULT_BAND_([0-9]+)";
    string Rad_Add_Regex = "RADIANCE_ADD_BAND_([0-9]+)";

    while(fgets(buffer, sizeof(buffer), this->mtl_file) != NULL){
        line = buffer;
        if(matches(line, CoorsRegex)){
            value = this->GetLineValue(line);
            this->coors_table.Add_Coordinate(c_coors, value);
            c_coors++;
        }
        else if(matches(line, Rad_Mult_Regex)){
            value = this->GetLineValue(line);
            this->radiancesData.Set_Mult_Rad(c_mult_rad, value);
            c_mult_rad++;
        }
        else if(matches(line, Rad_Add_Regex)){
            value = this->GetLineValue(line);
            this->radiancesData.Set_Add_Rad(c_add_rad, value);
            c_add_rad++;
        }
    }

    this->coors_table.PrintData();
    this->radiancesData.PrintData();
}
