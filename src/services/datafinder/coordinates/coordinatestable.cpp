#include "coordinatestable.h"

using namespace std;

CoordinatesTable::CoordinatesTable()
{

}

void CoordinatesTable::Add_Coordinate(int pos, double value){
    this->coordinates[pos] = value;
}

double* CoordinatesTable::Get_Coordinates(){
    return this->coordinates;
}

vector<Coords> CoordinatesTable::ArrayToVector(){
    vector<Coords> coordinates;
    for(int i  = 0; i < 4; i++){
        Coords coord(this->coordinates[i * 2], this->coordinates[(i * 2) + 1]);
        coordinates.push_back(coord);
    }
    return coordinates;
}

void CoordinatesTable::PrintData(){
    for(int i = 0; i < 8; i++)
        cout << "Coordinates: " << this->coordinates[i] << "\n";
}
