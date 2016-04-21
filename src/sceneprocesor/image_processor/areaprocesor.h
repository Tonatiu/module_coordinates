#ifndef AREAPROCESOR_H
#define AREAPROCESOR_H

#include <QtCore>
#include <opencv2/opencv.hpp>
#include <vector>
#include "../../calculator/filters/ndvi_filter.h"
#include "../../calculator/filters/pm10filter.h"
#include "../../postgis/postgis/entity/AreaObjetivo.h"
#include "../../postgis/geographic/BoundingBox.h"
#include "../scene_cutter/cutter.h"
#include "../scene_cutter/infoobjetivo.h"
#include "bandscontainer.h"

using namespace cv;

class AreaProcesor: QThread
{
public:
    AreaProcesor(BandsContainer* Bands, AreaObjetivo* target, BoundingBox* containerbounds);
private:
    void run();
    void ApliFilters();
    BandsContainer* Bands;
    AreaObjetivo *target;
    BoundingBox* countainer_bounds;
    float pm10_prom;
    float ndvi_prom;
};

#endif // AREAPROCESOR_H
