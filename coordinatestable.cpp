#include "coordinatestable.h"

using namespace std;

CoordinatesTable::CoordinatesTable()
{

}

void CoordinatesTable::addCellName(int position, string sceneName){
    this->CoorsTable[position].sceneName = (char *) malloc(sizeof(char) * sceneName.length());
    if(this->CoorsTable->sceneName == NULL)
        exit(0);
    strcpy(this->CoorsTable[position].sceneName, sceneName.c_str());
}

void CoordinatesTable::addValue(int cellPos, int position, double value){
    if(cellPos < this->tableSize && position < 8)
        this->CoorsTable[cellPos].coordinates[position] = value;
}

void CoordinatesTable::createTable(int tableSize){
    this->tableSize = tableSize;
    this->CoorsTable = (Scene_Coors *) malloc(sizeof(Scene_Coors) * tableSize);
    if(this->CoorsTable == NULL)
        exit(0);

    for(int i = 0; i < tableSize; i++){
        this->CoorsTable[i].coordinates = (double*) calloc(8, sizeof(double));
    }
}

void CoordinatesTable::printTable(){
    for(int i = 0; i < this->tableSize; i++){
        cout << i << " " << this->CoorsTable[i].sceneName << "\n";
        for(int j = 0; j < 8; j++){
            cout << this->CoorsTable[i].coordinates[j] << ";";
        }
        cout << "\n";
    }
}
