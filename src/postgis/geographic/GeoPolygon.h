#include <iostream>
#include <string>
#include "Coords.h"
#include "BoundingBox.h"

using namespace std;

#ifndef _GEOGRAPHIC_GEO_POLYGON_H_
    #define _GEOGRAPHIC_GEO_POLYGON_H_

    class GeoPolygon{
        string srid;
        string geomText;
        
        BoundingBox bounds;
        
        public:
            GeoPolygon(BoundingBox, string srid = "4326");
            GeoPolygon(string srid = "4326");
            GeoPolygon(string, string srid = "4326");
            
            void setSrid(string srid){
                this->srid = srid;
            }
            
            string getSrid(){
                return srid;
            }
            
            void setGeomText(string geomText){
                this->geomText = geomText;
            }
            
            string getGeomText(){
                return geomText;
            }
            
            void setBounds(BoundingBox bounds){
                this->bounds = bounds;
            }
            
            BoundingBox getBounds(){
                return bounds;
            }
    };

#endif