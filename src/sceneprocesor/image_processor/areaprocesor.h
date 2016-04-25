#ifndef AREAPROCESOR_H
#define AREAPROCESOR_H

#include <QtCore>
#include <opencv2/opencv.hpp>
#include <vector>
#include "../../calculator/filters/ndvi_filter.h"
#include "../../calculator/filters/pm10filter.h"
#include "../../postgis/postgis/entity/AreaObjetivo.h"
#include "../../postgis/geographic/BoundingBox.h"
#include "../../postgis/postgis/PostgisFunctions.h"
#include "../scene_cutter/cutter.h"
#include "../scene_cutter/infoobjetivo.h"
#include "bandscontainer.h"

using namespace cv;

class AreaProcesor: public QThread
{
public:
    AreaProcesor(BandsContainer* Bands, AreaObjetivo target, BoundingBox containerbounds, MTL_Data_Collector* collector);
private:
    void run();
    void AplyFilters();
    BandsContainer* Bands;
    AreaObjetivo target;
    BoundingBox countainer_bounds;
    PostgisFunctions functions_to_postgis;
    PM10Filter* filter_pm10;
    NDVI_Filter* filter_ndvi;
};

#endif // AREAPROCESOR_H
