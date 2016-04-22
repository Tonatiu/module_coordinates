#include "bandscontainer.h"

BandsContainer::BandsContainer(bool isL8)
{
    this->isL8 = isL8;
}

Mat BandsContainer::GentBandById(int id){
    return this->Bands[id];
}

bool BandsContainer::IsL8(){
    return this->isL8;
}

int BandsContainer::GetAlto(){
    return this->Bands[0].rows;
}

int BandsContainer::GetAncho(){
    return this->Bands[0].cols;
}

void BandsContainer::OpenBands(string origin, string name){
    string Band_path;

    if(this->isL8){
        for(int i = 0; i < 4; i++){
            Band_path = origin + "/" + name + "/" + name + "_B" + to_string(i + 2) + ".TIF";
            cout << Band_path << "\n";
            Mat B = imread(Band_path, IMREAD_GRAYSCALE);
            Bands.push_back(B);
        }
    }else{
        for(int i = 0; i < 4; i++){
            Band_path = origin + "/" + name + "/" + name + "_B" + to_string(i + 1) + ".TIF";
            cout << Band_path << "\n";
            Mat B = imread(Band_path, IMREAD_GRAYSCALE);

            Bands.push_back(B);
        }
    }
}
