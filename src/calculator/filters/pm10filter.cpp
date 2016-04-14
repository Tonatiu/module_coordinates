#include "pm10filter.h"

PM10Filter::PM10Filter(MTL_Data_Collector *collector): Filter(collector)
{
    this->empirical_values =(float*) calloc(3, sizeof(float));
}

void PM10Filter::SetEmpiricalValues(float a0, float a1, float a2){
    this->empirical_values[0] = a0;
    this->empirical_values[1] = a1;
    this->empirical_values[2] = a2;
}

bool PM10Filter::NoEmpiricalValues(){
    return  this->empirical_values == NULL ||
            (this->empirical_values[0] == 0 &&
             this->empirical_values[1] == 0 &&
             this->empirical_values[2] == 0);
}

float PM10Filter::PM10Calc(uchar red_pixel, uchar green_pixel, uchar blue_pixel){
    float PM10;
    float red_refl, green_refl, blue_refl;
    //Verificación de queexistan valores empíricos
    if(this->NoEmpiricalValues())
        return -1.0;
    //Cálculo de PM10 si el satélite es landsat 8
    if(this->isL8){
        red_refl = this->basicCalcs->RefelctanceCalc(red_pixel, RED_BAND + 1);
        green_refl = this->basicCalcs->RefelctanceCalc(green_pixel, GRE_BAND + 1);
        blue_refl = this->basicCalcs->RefelctanceCalc(blue_pixel, BLU_BAND + 1);
    }
    //Cálculo de PM10 en caso de que el satélite no sea landsat 8
    else{
        red_refl = this->basicCalcs->RefelctanceCalc(red_pixel, RED_BAND);
        green_refl = this->basicCalcs->RefelctanceCalc(green_pixel, GRE_BAND);
        blue_refl = this->basicCalcs->RefelctanceCalc(blue_pixel, BLU_BAND);
    }
    PM10 = blue_refl * this->empirical_values[0] +
           green_refl * this->empirical_values[1] +
           red_refl * this->empirical_values[2];

    return PM10;
}

float PM10Filter::PM10VectorProm(vector<uchar> red_vector, vector<uchar> green_vector, vector<uchar> blue_vector){
    int rowLength = red_vector.size();
    float PM10_prom = 0.0;
    //Obtención del promedio al iterar los tres vectores
    for(int i = 0; i < rowLength; i++){
        float PM10 = this->PM10Calc(red_vector[i], green_vector[i], blue_vector[i]);
        PM10_prom += PM10 / rowLength;
    }

    return PM10_prom;
}
