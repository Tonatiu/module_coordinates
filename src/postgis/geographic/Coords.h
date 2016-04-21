#include <iostream>
#include <string>
#include <sstream>

using namespace std;

#ifndef _GEOGRAPHIC_COORDS_H_
#define _GEOGRAPHIC_COORDS_H_

class Coords{
    double lat, lng;

    public:
        Coords(){}
        Coords(double, double);
        void setLat(double);
        void setLng(double);
        double getLat();
        double getLng();
        string toString();
};

#endif
