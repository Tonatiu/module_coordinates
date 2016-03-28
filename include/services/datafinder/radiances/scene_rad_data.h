#ifndef SCENE_RAD_DATA_H
#define SCENE_RAD_DATA_H
#include <stdlib.h>
#include <iostream>

using namespace std;

class Scene_Rad_Data
{
public:
    Scene_Rad_Data();
    void Set_Mult_Rad(int band, double value);
    void Set_Add_Rad(int band, double value);
    double* Get_Mult_Rads();
    double* Get_Add_Rads();
    void PrintData();
private:
    double *scene_mult_rads;
    double *scene_add_rads;
};

#endif // SCENE_RAD_DATA_H
