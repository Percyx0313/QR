//
// Created by 張耕維 on 2021/9/1.
//
#include <iostream>
#include "ZxCV.h"
#include "ZxConst.h"
#include <memory.h>
#include <math.h>
//===============================================
void Histogram(ZxImage& image,int* pHist){
    memset(pHist,0,256*sizeof(int));
    for(int i=0;i<image.nColNum*image.nRowNum;i++)
        pHist[image.m_pMemoryBase[i]]++;
}
//===============================================
void Equalization(ZxImage& image){
    int hist[256];
    int total_pixel=0;
    Histogram(image,hist);
    int pixel=hist[0];
    for(int i=1;i<256;i++){
        total_pixel+=hist[i];
        hist[i]+=hist[i-1];
    }
    for(int i=0;i<image.nRowNum;i++){
        for(int j=0;j<image.nColNum;j++){
            pixel = (image.m_pMatrixElement[i][j] + 0.5 < 255)
                    ? (int)(float(image.m_pMatrixElement[i][j]) + 0.5)
                    : 255;
            image.m_pMatrixElement[i][j]=int(float(hist[pixel])*255/float(total_pixel));
        }
    }
}
//===============================================
void Thresholding(ZxImage& src,ZxImage& dst,int value){
    dst.SetSize(src.nRowNum,src.nColNum);
    for(int i=0;i<src.nRowNum;i++) {
        for (int j = 0; j < src.nColNum; j++) {
            if(src.m_pMatrixElement[i][j]<=value)
                dst.m_pMatrixElement[i][j]=0;
            else
                dst.m_pMatrixElement[i][j]=255;
        }
    }
}
//===============================================
void Otsu_Threshold(ZxImage& src,ZxImage& dst){
    int hist[256];
    Histogram(src,hist);
    dst.SetSize(src.nRowNum,src.nColNum);
    int prefix_pixel[256]={0};
    int Expectation[256]={0};
    for(int i=1;i<256;i++) {
        prefix_pixel[i] = hist[i] + prefix_pixel[i - 1];
        Expectation[i]=hist[i]*i+Expectation[i-1];
    }

    // otsu between variance w_0/(1-w_0) * (E(X_0)-E(X))^2
    float max=0;
    int thrshold;
    float W_0,E_X_0,E_X,bt_var;
    E_X=float(Expectation[255])/float(prefix_pixel[255]);
    for(int i=1;i<256;i++){
        E_X_0=float(Expectation[i])/float(prefix_pixel[i]);
        W_0=float(prefix_pixel[i])/float(prefix_pixel[255]);
        bt_var=(W_0*(E_X_0-E_X)*(E_X_0-E_X)/(1-W_0));
        if(max<bt_var){
            max=bt_var;
            thrshold=i;
        }
    }
    Thresholding(src,dst,thrshold);
}
//===============================================
float Mean_Pixel(ZxImage& image){
    float Total_Pixel=0;
    int size=image.nColNum*image.nRowNum;
    for(int i=0;i<size;i++){
        Total_Pixel+=image.m_pMemoryBase[i];
    }
    return Total_Pixel/float(size);
}
//===============================================
float variance(ZxImage& image){
    float mean= Mean_Pixel(image);
    int size=image.nColNum*image.nRowNum;
    float Total_Pixel=0;
    for(int i=0;i<size;i++){
        Total_Pixel+=image.m_pMemoryBase[i]*image.m_pMemoryBase[i];
    }
    return sqrt(Total_Pixel/float(size)-mean*mean);
}
//===============================================
float Correlation(ZxImage& src,ZxImage& dst){
    if(src.nRowNum!= dst.nRowNum || src.nColNum!=dst.nColNum){
        return Zx_fMAX;
    }
    float mean1= Mean_Pixel(src);
    float mean2=Mean_Pixel(dst);
    float var1= variance(src);
    float var2= variance(dst);
    float temp=0;
    int size=src.nColNum*src.nRowNum;
    for(int i=0;i<size;i++){
        temp+=src.m_pMemoryBase[i]*dst.m_pMemoryBase[i];
    }
    return (temp-size*mean1*mean2)/(size*var1*var2);
}
//===============================================
ZxImage Filter(ZxImage& image,ZxMatrix& matrix){
    int edge_size=matrix.nRowNum/2;
    ZxImage dst(image.nRowNum,image.nColNum, true);
    PIXEL value;
    for(int i=edge_size;i<image.nRowNum-edge_size;i++){
        for(int j=edge_size;j<image.nColNum-edge_size;j++){
            value=0;
            for(int y=0;y<matrix.nRowNum;y++){
                for(int x=0;x<matrix.nColNum;x++){
                    value+=image.m_pMatrixElement[i+y-edge_size][j+x-edge_size]*matrix.m_pMatrixElement[y][x];
                }
            }
            dst.m_pMatrixElement[i][j]=value;
        }
    }
    return dst;
}