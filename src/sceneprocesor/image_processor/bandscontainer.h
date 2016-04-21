#ifndef BANDSCONTAINER_H
#define BANDSCONTAINER_H

#include <opencv2/opencv.hpp>
#include <string>

using namespace cv;
using namespace std;

class BandsContainer
{
public:
    BandsContainer(bool isL8);
    Mat *GetB_1();
    Mat *GetB_2();
    Mat *GetB_3();
    Mat *GetB_4();
    void OpenBands(string origin, string name);
    bool IsL8();
private:
    Mat B_1;
    Mat B_2;
    Mat B_3;
    Mat B_4;
    bool isL8;
};

#endif // BANDSCONTAINER_H
