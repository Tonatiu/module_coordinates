#include "filter.h"

Filter::Filter(MTL_Data_Collector *collector)
{
    this->basicCalcs = new Basics_Calculations(collector);
    this->isL8 = matches(collector->GetSpaceCraft(), "LANDSAT_8");
}
