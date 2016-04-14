#ifndef FILTER_H
#define FILTER_H

#include "../transforms/basics_calculations.h"
#include "../TT_Admin_3/src/services/datafinder/mtl_data_collector.h"
#include "../TT_Admin_3/src/t_regex/t_regex.h"

//Definidos para landsat x < 8
#define BLU_BAND 1
#define GRE_BAND 2
#define RED_BAND 3
#define NIR_BAND 4

class Filter
{
public:
    Filter(MTL_Data_Collector* collector);
protected:
    Basics_Calculations* basicCalcs;
    bool isL8;
};

#endif // FILTER_H
