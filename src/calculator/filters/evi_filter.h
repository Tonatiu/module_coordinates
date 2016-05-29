#ifndef EVI_FILTER_H
#define EVI_FILTER_H

#include "filter.h"

class EVI_Filter : public Filter
{
public:
    EVI_Filter(MTL_Data_Collector* collector);
    //Permite recorrer un row de pixeles para obtener el EVI promedio
    //float EVI_Vector_Prom(vector<uchar> vis_row, vector<uchar> nir_row);
    float EVI_Calc(uchar vis_pixel, uchar nir_pixel, uchar blue_pixel);
};

#endif // EVI_FILTER_H