#include <iostream>
#include "ZxLib/ZxCV.h"
#include "ZxLib/ZxAPI.h"
#include <opencv2/opencv.hpp>
#include "ZxLib/ZxImageTool.h"
using namespace std;
using namespace cv;
//======================
float filter_entry[9]={-1,-2,-1,0,0,0,1,2,1};
float filter_entry2[9]={-1,0,1,-2,0,2,-1,0,1};
int main() {
    ZxImage image(10,10);
    ZxImage image2;
    ZxImage image3;
    ZxMatrix M(3,3);
    for(int i=0;i<9;i++){
        M.m_pMemoryBase[i]=filter_entry[i];
    }
    image=my_read("../Image/face.tif");
    my_show("origin",image);
    image2=Filter(image,M);
    for(int i=0;i<9;i++){
        M.m_pMemoryBase[i]=filter_entry2[i];
    }
    image3=Filter(image,M);
    image2=image+image3;
    my_show("dst",image2);
    waitKey(0);
    return 0;
}
