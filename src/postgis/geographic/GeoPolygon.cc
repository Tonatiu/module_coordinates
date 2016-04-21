#include "GeoPolygon.h"


GeoPolygon::GeoPolygon(string srid): srid(srid){}


GeoPolygon::GeoPolygon(string geomText, string srid): geomText(geomText),srid(srid){}


GeoPolygon::GeoPolygon(BoundingBox bounds, string srid){
    this->bounds = bounds;
    this->srid = srid;
}
