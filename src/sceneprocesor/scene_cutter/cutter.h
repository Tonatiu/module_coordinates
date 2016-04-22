#ifndef CUTTER_H
#define CUTTER_H

#include "infoobjetivo.h"
#include "../../postgis/geographic/BoundingBox.h"

InfoObjetivo *CoorsToPixel(BoundingBox target, int img_high, int img_width, BoundingBox container);

#endif // CUTTER_H
