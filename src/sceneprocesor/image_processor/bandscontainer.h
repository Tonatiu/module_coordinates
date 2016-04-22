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
    Mat GentBandById(int id);
    void OpenBands(string origin, string name);
    bool IsL8();
    int GetAlto();
    int GetAncho();
private:
    vector<Mat> Bands;
    bool isL8;
};

#endif // BANDSCONTAINER_H
