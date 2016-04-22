#ifndef PM10FILTER_H
#define PM10FILTER_H

#include "filter.h"

using namespace std;

class PM10Filter : public Filter
{
public:
    PM10Filter(MTL_Data_Collector *collector);
    //Añade los valores empíricos para calcular PM10
    void SetEmpiricalValues(float a0, float a1, float a2);
    //Calcula el PM10 para un pixel
    float PM10Calc(uchar red_pixel, uchar green_pixel, uchar blue_pixel);
private:
    /*Métodos privados*/
    //Regresa true si no existen valores empíricos
    bool NoEmpiricalValues();
    //Calcula el promedio de PM10 para un vector de la escena
    float PM10VectorProm(vector<uchar> red_vector, vector<uchar> green_vector, vector<uchar> blue_vector);
    /*Atributos privados*/
    float* empirical_values;

};

#endif // PM10FILTER_H
