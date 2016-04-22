#include "Coords.h"


Coords::Coords(double lat, double lng){
    this->lat = lat;
    this->lng = lng;
}


void Coords::setLat(double lat){
    this->lat = lat;
}


void Coords::setLng(double lng){
    this->lng = lng;
}


double Coords::getLat(){
    return lat;
}


double Coords::getLng(){
    return lng;
}


string Coords::toString(){
    ostringstream strs_lat;
    ostringstream strs_lng;
    
    strs_lng << lng;
    string str_lng = strs_lng.str();
    
    strs_lat << lat;
    string str_lat = strs_lat.str();

    string text(str_lng);
    text.append(" ");
    text.append(str_lat);
    
    return text;
}
