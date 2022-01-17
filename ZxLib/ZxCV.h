//
// Created by 張耕維 on 2021/8/31.
//
#ifndef CV_ZXCV_H
#define CV_ZXCV_H
#include <iostream>
#include <vector>
#include "ZxConst.h"
/*!@file ZxCV.h
 * @author Percy
 * @brief This file give some basic CV object
 */


class ZxPoint{
public:
    float x;
    float y;
    //===========================================
    ///@brief Constructor which default is zeros
    ZxPoint(float _x=0,float _y=0);
    ///@brief Operator =
    ZxPoint& operator=(ZxPoint that);
    ///@brief Operator +=
    ZxPoint& operator+=(ZxPoint that);
    ///@brief Operator -=
    ZxPoint& operator-=(ZxPoint that);
    ///@brief Operator ==
    bool operator==(ZxPoint that);
    ///@brief Operator +
    ZxPoint operator+(ZxPoint that);
    ///@brief Operator -
    ZxPoint operator-(ZxPoint that);
    ///@brief Operator !=
    bool operator!=(ZxPoint that);
    ///@brief Scalar multiply
    ZxPoint operator*(float scalar);
    ///@brief Scalar division
    ZxPoint operator/(float scalar);
    ///@brief inner product
    float operator*(ZxPoint that);
    ///@brief Set the point value
    void operator()(float _x,float _y);
    ///@brief Compute the midpoint of two point
    ZxPoint MidPoint(ZxPoint that);
    ///@brief Set x and y to 0
    void Clear();
    ///@brief Set x and y to NULL
    void SetNull();
    ///@brief Determine whether the point is NULL
    bool IsNull();
    ///@brief Determine whether the point is (0,0)
    bool IsZero();
    ///@brief Change two point value
    void Swap(ZxPoint &that);
    ///@brief Compute the norm of vector
    float Norm();
    ///@brief Compute distance of two points
    float Distance(ZxPoint that);
    ///@brief Project this point to that point
    ZxPoint Projection(ZxPoint &that);
};

class ZxImage{
public:
    PIXEL* m_pMemoryBase;
    PIXEL** m_pMatrixElement;
    int nRowNum;
    int nColNum;
    //===========================================
    ZxImage(int _nRowNum=0,int _nColNum=0,bool clear=false);
    ZxImage(ZxImage &imCopyForm);
    ~ZxImage();
    ZxImage& operator=(const ZxImage &imCopyForm);
    ZxImage operator+(const ZxImage &imImage);
    ZxImage operator-(const ZxImage &imImage);
    void SetSize(int _nRowNum, int _nColNum, bool clear = false);
    void Clear();
    void SetTo(PIXEL value);
};

class ZxMatrix{
public:
    float* m_pMemoryBase;
    float** m_pMatrixElement;
    int nRowNum;
    int nColNum;
    //===========================================
    ZxMatrix(int _nRowNum=0,int _nColNum=0,bool clear=false);
    ~ZxMatrix();
    ZxMatrix& operator=(ZxMatrix& operand);
    ZxMatrix& operator+=(ZxMatrix& operand);
    ZxMatrix& operator-=(ZxMatrix& operand);
    ZxMatrix operator+(ZxMatrix& operand);
    ZxMatrix operator-(ZxMatrix& operand);
    ZxMatrix& operator+=(float scalar);
    ZxMatrix& operator-=(float scalar);
    ZxMatrix operator*(float scalar);
    ZxMatrix operator/(float scalar);
    void Clear();
    void Resize(int _nRowNum=0,int _nColNum=0,bool clear=false);
};
/// @brief color image BGR like OpenCV
class ZxColor{
public:
    PIXEL B;
    PIXEL G;
    PIXEL R;
    //===========================================
    ZxColor(int _B,int _G,int _R);
    ZxColor operator()(int _B,int _G,int _R);
    ZxColor& operator=(ZxColor CopyColor);
};
class ZxColorImage{
public:
    std::vector< std::vector<std::vector<PIXEL> > > m_pMatrixElement;
    int nRowNum;
    int nColNum;
    //===========================================
    ZxColorImage(int _nRowNum=0,int _nColNum=0);
    void DrawPoint(ZxPoint pt,ZxColor color);
    void DrawLine(ZxPoint pt1,ZxPoint pt2,ZxColor color,float ThickNess=1);
    void DrawCircle(ZxPoint origin,float radius,ZxColor color,float ThickNess=1);
    bool ValidPoint(int x,int y);

};
#endif //CV_ZXCV_H
