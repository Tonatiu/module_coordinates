#include <iostream>
#include <pqxx/pqxx>
#include <vector>
#include <string>
#include <string.h>
#include <stdlib.h>

#include "postgis.h"
#include "../geographic/GeoPolygon.h"
#include "../geographic/GeoPoint.h"
#include "../geographic/BoundingBox.h"
#include "entity/AreaObjetivo.h"
#include <QtCore>

using namespace std;
using namespace pqxx;

#ifndef _POSTGIS_POSTGIS_FUNCTIONS_H_
#define _POSTGIS_POSTGIS_FUNCTIONS_H_

string propertyToString(string, string, bool last = false);
string propertyToString(string, float, bool last = false);
BoundingBox parseBoundingBox(string);
BoundingBox parseBoundingBox(char *);

class PostgisFunctions{
public:
    static string getTableSrid(string, string geometry_column = "geom");
    static GeoPolygon getBounds(GeoPoint, GeoPoint);
    static vector<AreaObjetivo> getAreasObjetivo(BoundingBox);
    bool insertAreaObjetivo(AreaObjetivo);
private:
    QMutex mutex;
};
#endif
