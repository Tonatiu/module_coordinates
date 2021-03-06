#include "areaprocesor.h"

AreaProcesor::AreaProcesor(BandsContainer* Bands, AreaObjetivo target, BoundingBox containerbounds, MTL_Data_Collector *collector)
{
    this->Bands = Bands;
    this->target = target;
    this->countainer_bounds = containerbounds;
    this->filter_ndvi = new NDVI_Filter(collector);
    this->filter_pm10 = new PM10Filter(collector);
    this->filter_pm10->SetEmpiricalValues(410,253,-205);
}

void AreaProcesor::AplyFilters(){
    uchar red, green, blue, nir;

    float ndvi_prom = 0.0;
    float pm10_prom = 0.0;

    int height, width;
    height = Bands->GetAlto();
    width = Bands->GetAncho();

    InfoObjetivo *info = CoorsToPixel(target.getBounds(), height, width, countainer_bounds);

    int pos_x = info->GetUL_X();
    int pos_y = info->GetUL_Y();
    int num_elements = info->GetAlto() * info->GetAncho();
    for(int row = 0; row < info->GetAlto(); row++){
        for(int col = 0; col < info->GetAncho(); col++){
            blue = Bands->GentBandById(0).at<uchar>((pos_y + col), (pos_x + row));
            green = Bands->GentBandById(1).at<uchar>((pos_y + col), (pos_x + row));
            red = Bands->GentBandById(2).at<uchar>((pos_y + col), (pos_x + row));
            nir = Bands->GentBandById(3).at<uchar>((pos_y + col), (pos_x + row));
            ndvi_prom += filter_ndvi->NDVI_Calc(red, nir) ;
            pm10_prom += filter_pm10->PM10Calc(red, green, blue);
        }
    }
    if(num_elements != 0){
        ndvi_prom = ndvi_prom / num_elements;
        pm10_prom = pm10_prom / num_elements;
    }
    else{
        ndvi_prom = 0;
        pm10_prom = 0;
    }
    target.setPorcentajeContaminacion(pm10_prom);
    target.setporcentajeVegetacion(ndvi_prom);
}

void AreaProcesor::run(){
    AplyFilters();
    if(this->functions_to_postgis.insertAreaObjetivo(this->target)){
        cout << "Insert OK\n";
    }
    return;
}
