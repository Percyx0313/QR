//
// Created by 張耕維 on 2021/9/2.
//
#include <iostream>
#include <opencv2/opencv.hpp>
#include "ZxAPI.h"
#include "ZxCV.h"
#include "ZxImageTool.h"
using namespace std;
using namespace cv;
//===============================================
ZxImage my_read(string file){
    Mat temp=imread(file);
    cvtColor(temp,temp,COLOR_BGR2GRAY);
    ZxImage image;
    image.SetSize(temp.rows,temp.cols);
    for(int i=0;i<temp.rows;i++){
        for(int j=0;j<temp.cols;j++){
            image.m_pMatrixElement[i][j]=temp.data[i*temp.cols+j];
        }
    }
    return image;
}
//===============================================
void my_show(string box_name,ZxImage& image){
    Mat temp(image.nRowNum,image.nColNum,CV_8UC1,Scalar(0,0,0));
    for(int i=0;i<temp.rows;i++){
        for(int j=0;j<temp.cols;j++){
            temp.data[i*temp.cols+j]=image.m_pMatrixElement[i][j];
        }
    }
    imshow(box_name,temp);
}
//===============================================
void my_show(string box_name,ZxColorImage& image){
    Mat temp(image.nRowNum,image.nColNum,CV_8UC3,Scalar(0,0,0));
    for(int i=0;i<temp.rows;i++){
        for(int j=0;j<temp.cols;j++){
            for(int k=0;k<3;k++) {
                temp.at<Vec3b>(i, j)[k] = image.m_pMatrixElement[i][j][k];
            }
        }
    }
    imshow(box_name,temp);
}
//===============================================
Mat& GetMat(ZxImage& image,bool color){
    Mat* temp;
    if(color)
        temp= new Mat(image.nRowNum, image.nColNum, CV_8UC3, Scalar(0, 0, 0));
    else
        temp= new Mat(image.nRowNum, image.nColNum, CV_8UC1, Scalar(0, 0, 0));
    for(int i=0;i<image.nRowNum*image.nColNum;i++){
        temp->data[i]=image.m_pMemoryBase[i];
    }
    return *temp;
}
//===============================================
void show_hist(ZxImage& image){
    int hist[256];
    int hist_h=400;
    int hist_w=512;
    float bin=float(hist_w)/256;
    Histogram(image,hist);
    int max=0;
    for(int i=0;i<256;i++) {
        if (hist[i] > hist[max]) max = i;
    }

    float h_bin=float(hist_h)/float(hist[max]);
    ZxPoint pt1,pt2(0,float(float(hist_h)-float(hist[0])*h_bin));
    ZxColorImage Hist_image(hist_h,hist_w);
    for(int i=1;i<256;i++){
        pt1=pt2;
        pt2=ZxPoint(bin*i,float(hist_h)-float(hist[i])*h_bin);
        Hist_image.DrawLine(pt1,pt2,ZxColor(255,255,255),2);
    }
    my_show("Historgram",Hist_image);
}
