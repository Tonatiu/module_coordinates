#include "bandscontainer.h"

BandsContainer::BandsContainer(bool isL8)
{
    this->isL8 = isL8;
}

Mat* BandsContainer::GetB_1(){
    return &this->B_1;
}

Mat* BandsContainer::GetB_2(){
    return &this->B_2;
}

Mat* BandsContainer::GetB_3(){
    return &this->B_3;
}

Mat* BandsContainer::GetB_4(){
    return &this->B_4;
}

bool BandsContainer::IsL8(){
    return this->isL8;
}

void BandsContainer::OpenBands(string origin, string name){
    string Band_path;

    if(this->isL8){
        //blue
        Band_path = origin + name + "/" + name + "_B2.TIF";
        this->B_1 = imread(Band_path);
        //green
        Band_path = origin + name + "/" + name + "_B3.TIF";
        this->B_2 = imread(Band_path);
        //red
        Band_path = origin + name + "/" + name + "_B4.TIF";
        this->B_3 = imread(Band_path);
        //nir
        Band_path = origin + name + "/" + name + "_B5.TIF";
        this->B_4 = imread(Band_path);
    }else{
        //blue
        Band_path = origin + name + "/" + name + "_B1.TIF";
        this->B_1 = imread(Band_path);
        //green
        Band_path = origin + name + "/" + name + "_B2.TIF";
        this->B_2 = imread(Band_path);
        //red
        Band_path = origin + name + "/" + name + "_B3.TIF";
        this->B_3 = imread(Band_path);
        //nir
        Band_path = origin + name + "/" + name + "_B4.TIF";
        this->B_4 = imread(Band_path);
    }
}
