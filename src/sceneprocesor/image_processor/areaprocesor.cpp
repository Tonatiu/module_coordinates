#include "areaprocesor.h"

AreaProcesor::AreaProcesor(BandsContainer* Bands, AreaObjetivo* target, , BoundingBox *containerbounds)
{
    this->Bands = Bands;
    this->target = target;
    this->countainer_bounds = containerbounds;
    this->pm10_prom = 0.0;
    this->ndvi_prom = 0.0;

}

void AreaProcesor::ApliFilters(){
    PM10Filter filter_pm10;
    NDVI_Filter filter_ndvi;
    filter_pm10.SetEmpiricalValues(600,350,480);
    uchar red, green, blue, nir;

    int height, width;
    height = Bands->GetB_1()->rows;
    width = Bands->GetB_1()->cols;
    Bands->GetB_1()->at<uchar>;
    InfoObjetivo info = CoorsToPixel(target->getBounds(), height, width, *countainer_bounds);

    int num_elements = info.GetAlto() * info.GetAncho();

    for(int row = 0; row < info.GetAlto(); row++){
        for(int col = 0; col < info.GetAncho(); col++){
            int pos_x = info.GetUL_X() + row;
            int pos_y = info.GetUL_Y() + col;

            blue = Bands->GetB_1()->at<uchar>(pos_x, pos_y);
            green = Bands->GetB_2()->at<uchar>(pos_x, pos_y);
            red = Bands->GetB_3()->at<uchar>(pos_x, pos_y);
            nir = Bands->GetB_4()->at<uchar>(pos_x, pos_y);

            ndvi_prom = (ndvi_prom + filter_ndvi.NDVI_Calc(red, nir)) / num_elements;
            pm10_prom = (pm10_prom + filter_pm10.PM10Calc(red, gree, blue)) / num_elements;
        }
    }
}

void AreaProcesor::run(){
    ApliFilters();
}
