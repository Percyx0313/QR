//
// Created by 張耕維 on 2021/9/2.
//

#ifndef CV_ZXAPI_H
#define CV_ZXAPI_H
#include <iostream>
#include "ZxCV.h"
#include "opencv2/opencv.hpp"
using  namespace std;
using  namespace cv;
ZxImage my_read(string file);
void my_show(string box_name,ZxImage& image);
void my_show(string box_name,ZxColorImage& image);
Mat& GetMat(ZxImage& image,bool color=true);
void show_hist(ZxImage& image);
#endif //CV_ZXAPI_H
