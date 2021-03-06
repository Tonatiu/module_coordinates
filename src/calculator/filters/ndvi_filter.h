#ifndef NDVI_FILTER_H
#define NDVI_FILTER_H

#include "filter.h"

class NDVI_Filter : public Filter
{
public:
    NDVI_Filter(MTL_Data_Collector* collector);
    //Permite recorrer un row de pixeles para obtener el NDVI promedio
    float NDVI_Vector_Prom(vector<uchar> vis_row, vector<uchar> nir_row);
    float NDVI_Calc(uchar vis_pixel, uchar nir_pixel);
};

#endif // NDVI_FILTER_H
