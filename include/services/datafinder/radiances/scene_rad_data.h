#ifndef SCENE_RAD_DATA_H
#define SCENE_RAD_DATA_H
#include <stdlib.h>
#include <iostream>

using namespace std;
//La clase almacenará las constantes necesarias para la obtención de la radianza
class Scene_Rad_Data
{
public:
    Scene_Rad_Data();
    //Añade un valor multipicativo a la banda band
    void Set_Mult_Rad(int band, double value);
    //Añade n valor aditivo a la bada band
    void Set_Add_Rad(int band, double value);
    //Devuelve el apuntador a los valores multiplicativos
    double* Get_Mult_Rads();
    //Devuelve un apuntador a los valores aditivos
    double* Get_Add_Rads();
    //Método de prueba. Permite imprimir el contenido de la clase
    void PrintData();
private:
    //Valores multiplicativos
    double *scene_mult_rads;
    //Valores aditivos
    double *scene_add_rads;
};

#endif // SCENE_RAD_DATA_H
