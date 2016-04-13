#include "scene_rad_data.h"

Scene_Rad_Data::Scene_Rad_Data()
{
    //Inicialización de los vectores de radiancias. Se usa un tamaño de 11 en caso de que
    //las escenas pertenezcan a landzat 8
    this->scene_add_rads = (double *) calloc(11, sizeof(double));
    this->scene_mult_rads = (double *) calloc(11, sizeof(double));
}

void Scene_Rad_Data::Set_Add_Rad(int band, double value){
    this->scene_add_rads[band] = value;
}
void Scene_Rad_Data::Set_Mult_Rad(int band, double value){
    this->scene_mult_rads[band] = value;
}

double* Scene_Rad_Data::Get_Add_Rads(){
    return this->scene_add_rads;
}

double* Scene_Rad_Data::Get_Mult_Rads(){
    return this->scene_mult_rads;
}

void Scene_Rad_Data::PrintData(){
    for(int i = 0; i < 11; i++){
        cout << this->scene_add_rads[i] << "\n";
        cout << this->scene_mult_rads[i] << "\n";
    }
}
