#include "basics_calculations.h"

Basics_Calculations::Basics_Calculations(MTL_Data_Collector *data_collector){
    this->data_collector = data_collector;
}

float Basics_Calculations::RadianceCalc(uchar pixel, int band){
    //El cálculo de la radiancia es sencillo gracias a las constantes que ofrece el MTL
    double factor = this->data_collector->GetRadData()->Get_Mult_Rads()[band];
    double bias = this->data_collector->GetRadData()->Get_Add_Rads()[band];
    return (float)pixel * factor + bias;
}

float Basics_Calculations::RefelctanceCalc(uchar pixel, int band){
    int year, month, day;
    string s_year, s_month, s_day;
    double ro;
    double radiance, sun_distance;
    //Obtención de los valores YY MM dd de forma individual a partir de la fecha obtenida del colector de datos
    s_year = this->data_collector->GetAquiredDate().substr(0, 4);
    s_month = this->data_collector->GetAquiredDate().substr(5, 7);
    s_day = this->data_collector->GetAquiredDate().substr(8, 10);
    //Conversiones de strings a valores enteros
    year = atoi(s_year.c_str());
    month = atoi(s_month.c_str());
    day = atoi(s_day.c_str());
    //Obtención del número del día del año necesario para calcular la distancia solar
    boost::gregorian::date d(year, month, day);
    int daynumber = d.day_of_year();
    //Cálculo de la distancia solar
    sun_distance = 1 - (.01674 * cos(.9856 * daynumber));
    //Obtención de la radiancia
    radiance = this->RadianceCalc(pixel, band);
    //Conversión a reflectancia
    ro = (PI * radiance * sqrt(sun_distance))
            / (this->ESUN[band] * cos(this->data_collector->GetAzimuth()));

    return ro;
}
