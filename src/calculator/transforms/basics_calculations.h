#ifndef BASICS_CALCULATIONS_H
#define BASICS_CALCULATIONS_H

#include <math.h>
#include <boost/date_time/gregorian/gregorian.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <vector>
#include "../../../src/services/datafinder/mtl_data_collector.h"

#define PI 3.1415926535898

using namespace std;
using namespace cv;

//La clase permite operar los pixeles para obtener su radiancia y refectancia
class Basics_Calculations
{
public:
    //El cosntructor requiere los datos almacenados en un colector de datos
    Basics_Calculations(MTL_Data_Collector *data_collector);
    //Permite calcular la radiancia de un pixel de la banda band
    float RadianceCalc(uchar pixel, int band);
    //Permite clacular la reflectancia de un pixel de la banda band
    float RefelctanceCalc(uchar pixel, int band);
private:
    //Apuntador al colector de datos
    MTL_Data_Collector* data_collector;
    //Valores por defecto de ESUN, necesarios para la conversión radianza-reflectancia
    double ESUN[8] = {1970, 1842, 1547, 1044, 225.7, 82.06, 1369};
};
#endif // BASICS_CALCULATIONS_H
