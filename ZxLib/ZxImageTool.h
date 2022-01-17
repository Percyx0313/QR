//
// Created by 張耕維 on 2021/9/1.
//

#ifndef CV_ZXIMAGETOOL_H
#define CV_ZXIMAGETOOL_H
///@brief get the histogram from the image
///@param image:source image
///@param pHist:256 length array
void Histogram(ZxImage& image,int* pHist);
void Equalization(ZxImage& image);
void Thresholding(ZxImage& src,ZxImage& dst,int value);
void Otsu_Threshold(ZxImage& src,ZxImage& dst);
float Correlation(ZxImage& src,ZxImage& det);
float Mean_Pixel(ZxImage& image);
float variance(ZxImage& image);
ZxImage Filter(ZxImage& image,ZxMatrix& matrix);
#endif //CV_ZXIMAGETOOL_H
