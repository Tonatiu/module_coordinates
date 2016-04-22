#include "BoundingBox.h"


BoundingBox::BoundingBox(Coords left_top, Coords right_top, Coords left_bottom, Coords right_bottom){
    this->left_top = left_top;
    this->right_top = right_top;
    this->right_bottom = right_bottom;
    this->left_bottom = left_bottom;
}

BoundingBox::BoundingBox(vector<Coords> Coordinates){
    this->left_top = Coordinates[0];
    this->right_top = Coordinates[1];
    this->left_bottom = Coordinates[2];
    this->right_bottom = Coordinates[3];
}

string BoundingBox::getPolygonWKT(){
    string text("POLYGON((");
    text.append(left_bottom.toString());
    text.append(",");
    text.append(left_top.toString());
    text.append(",");
    text.append(right_top.toString());
    text.append(",");
    text.append(right_bottom.toString());
    text.append(",");
    text.append(left_bottom.toString());
    text.append("))");
    
    return text;
}
