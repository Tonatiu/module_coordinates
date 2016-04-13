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

void CoordinatesTable::PrintData(){
    for(int i = 0; i < 8; i++)
        cout << "Coordinates: " << this->coordinates[i] << "\n";
}
