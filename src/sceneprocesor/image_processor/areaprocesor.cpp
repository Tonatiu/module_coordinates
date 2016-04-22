#include "areaprocesor.h"

AreaProcesor::AreaProcesor(BandsContainer* Bands, AreaObjetivo target, BoundingBox containerbounds, PM10Filter* filter_pm10, NDVI_Filter* filter_ndvi)
{
    this->Bands = Bands;
    this->target = target;
    this->countainer_bounds = containerbounds;
    this->filter_ndvi = filter_ndvi;
    this->filter_pm10 = filter_pm10;
    this->filter_pm10->SetEmpiricalValues(600,350,480);
}

void AreaProcesor::AplyFilters(){
    uchar red, green, blue, nir;

    float ndvi_prom = 0.0;
    float pm10_prom = 0.0;

    int height, width;
    height = Bands->GetAlto();
    width = Bands->GetAncho();

    InfoObjetivo *info = CoorsToPixel(target.getBounds(), height, width, countainer_bounds);

    int num_elements = info->GetAlto() * info->GetAncho();
    cout << "Alto, ancho " << info->GetAlto() << ", " << info->GetAncho() << "\n";
    for(int row = 0; row < info->GetAlto(); row++){
        for(int col = 0; col < info->GetAncho(); col++){
            int pos_x = info->GetUL_X() + row;
            int pos_y = info->GetUL_Y() + col;
            cout << pos_x << ", " << pos_y << "\n";
            blue = Bands->GentBandById(0).at<uchar>(pos_x, pos_y);
            green = Bands->GentBandById(1).at<uchar>(pos_x, pos_y);
            red = Bands->GentBandById(2).at<uchar>(pos_x, pos_y);
            nir = Bands->GentBandById(3).at<uchar>(pos_x, pos_y);
            cout << blue << ", " << green << ", " << red << ", " << nir << "\n";
            ndvi_prom = (ndvi_prom + filter_ndvi->NDVI_Calc(red, nir)) / num_elements;
            pm10_prom = (pm10_prom + filter_pm10->PM10Calc(red, green, blue)) / num_elements;
        }
    }
    cout << "pm10 " << pm10_prom << "\n";
    cout << "ndvi " << ndvi_prom << "\n";
    target.setPorcentajeContaminacion(pm10_prom);
    target.setporcentajeVegetacion(ndvi_prom);
}

void AreaProcesor::run(){
    AplyFilters();
    /*if(this->functions_to_postgis.insertAreaObjetivo(this->target)){
        //cout << "Insert OK";
    }*/
}
