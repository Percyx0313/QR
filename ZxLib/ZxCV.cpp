//
// Created by 張耕維 on 2021/8/31.
//

#include <iostream>
#include <cmath>
#include <memory.h>
#include "ZxCV.h"
#include "ZxConst.h"
//===============================================
ZxPoint::ZxPoint(float _x, float _y) {
    x=_x;
    y=_y;
}
//===============================================
ZxPoint& ZxPoint::operator=(ZxPoint that){
    x=that.x;
    y=that.y;
    return *this;
}
//===============================================
ZxPoint& ZxPoint::operator+=(ZxPoint that){
    x+=that.x;
    y+=that.y;
    return *this;
}
//===============================================
ZxPoint& ZxPoint::operator-=(ZxPoint that){
    x-=that.x;
    y-=that.y;
    return *this;
}
//===============================================
bool ZxPoint::operator==(ZxPoint that){
    if(x==that.x && y==that.y) return true;
    return false;
}
//===============================================
ZxPoint ZxPoint::operator+(ZxPoint that){
    ZxPoint temp(x+that.x,y+that.y);
    return temp;
}
//===============================================
ZxPoint ZxPoint::operator-(ZxPoint that){
    ZxPoint temp(x-that.x,y-that.y);
    return temp;
}
//===============================================
bool ZxPoint::operator!=(ZxPoint that){
    if(x!=that.x || y!=that.y) return true;
    return false;
}
//===============================================
ZxPoint ZxPoint::operator*(float scalar){
    ZxPoint temp(x*scalar,y*scalar);
    return temp;
}
//===============================================
ZxPoint ZxPoint::operator/(float scalar){
    ZxPoint temp(x/scalar,y/scalar);
    return temp;
}
//===============================================
float ZxPoint::operator*(ZxPoint that){
    return (x*that.x+y*that.y);
}
//===============================================
void ZxPoint::operator()(float _x,float _y){
    x=_x;
    y=_y;
}
//===============================================
ZxPoint ZxPoint::MidPoint(ZxPoint that){
    ZxPoint temp((x+that.x)/2,(y+that.y)/2);
    return temp;
}
//===============================================
void ZxPoint::Clear(){
    x=0;
    y=0;
}
//===============================================
void ZxPoint::SetNull(){
    x=Zx_INT32_MAX;
    y=Zx_INT32_MAX;
}
//===============================================
bool ZxPoint::IsNull(){
    if(x==Zx_INT32_MAX || y==Zx_INT32_MAX) return true;
    return false;
}
//===============================================
bool ZxPoint::IsZero(){
    if(x==0 && y==0)return true;
    return false;
}
//===============================================
void ZxPoint::Swap(ZxPoint &that){
    float temp=x;
    x=that.x;
    that.x=temp;
    temp=y;
    y=that.y;
    that.y=temp;
}
//===============================================
float ZxPoint::Norm(){
    return sqrt(x*x+y*y);
}
//===============================================
float ZxPoint::Distance(ZxPoint that){
    return sqrt((x-that.x)*(x-that.x)+(y-that.y)*(y-that.y));
}
//===============================================
ZxPoint ZxPoint::Projection(ZxPoint &that){
    ZxPoint temp;
    float len;
    len=that.x*that.x+that.y*that.y;
    temp=that*((*this)*that/len);
    return temp;
}
//===============================================
ZxImage::ZxImage(int _nRowNum,int _nColNum,bool clear){
    nColNum=_nColNum;
    nRowNum=_nRowNum;
    m_pMemoryBase=new PIXEL [nRowNum*nColNum];
    m_pMatrixElement=new PIXEL* [nRowNum];
    PIXEL* p=m_pMemoryBase;
    for(int i=0;i<nRowNum;i++,p+=nColNum){
        m_pMatrixElement[i]=p;
        if(clear)
            memset(m_pMemoryBase,0,sizeof (PIXEL)*nColNum);
    }
}
//===============================================
ZxImage::ZxImage(ZxImage &imCopyForm){
    SetSize(imCopyForm.nRowNum,imCopyForm.nColNum);
    for(int i=0;i<nRowNum;i++){
        for(int j=0;j<nColNum;j++){
            m_pMatrixElement[i][j]=imCopyForm.m_pMatrixElement[i][j];
        }
    }
}
////===============================================
ZxImage::~ZxImage(){
    delete [] m_pMemoryBase;
    delete [] m_pMatrixElement;
}
//===============================================
ZxImage& ZxImage::operator=(const ZxImage &imCopyForm){
    SetSize(imCopyForm.nRowNum,imCopyForm.nColNum);
    for(int i=0;i<nRowNum;i++){
        for(int j=0;j<nColNum;j++){
            m_pMatrixElement[i][j]=imCopyForm.m_pMatrixElement[i][j];
        }
    }
    return *this;
}
////===============================================
ZxImage ZxImage::operator+(const ZxImage &imImage) {
    ZxImage temp;
    if(nRowNum!=imImage.nRowNum || nColNum!=imImage.nColNum)
        return temp;
    temp.SetSize(nRowNum,nColNum);
    for(int i=0;i<nRowNum;i++){
        for(int j=0;j<nColNum;j++){
            if(m_pMatrixElement[i][j]+imImage.m_pMatrixElement[i][j]>255)
                temp.m_pMatrixElement[i][j]=255;
            temp.m_pMatrixElement[i][j]=m_pMatrixElement[i][j]+imImage.m_pMatrixElement[i][j];
        }
    }
    return temp;
}
////===============================================
ZxImage ZxImage::operator-(const ZxImage &imImage){
    ZxImage temp;
    if(nRowNum!=imImage.nRowNum || nColNum!=imImage.nColNum)
        return temp;
    temp.SetSize(nRowNum,nColNum);
    for(int i=0;i<nRowNum;i++){
        for(int j=0;j<nColNum;j++){
            if(m_pMatrixElement[i][j]-imImage.m_pMatrixElement[i][j]<0)
                temp.m_pMatrixElement[i][j]=0;
            temp.m_pMatrixElement[i][j]=m_pMatrixElement[i][j]-imImage.m_pMatrixElement[i][j];
        }
    }
    return temp;
}
//===============================================
void ZxImage::SetSize(int _nRowNum, int _nColNum, bool clear){
    if(nRowNum==_nRowNum &&nColNum==_nColNum){
        if(clear)
            Clear();
        return ;
    }else{
        delete [] m_pMemoryBase;
        delete [] m_pMatrixElement;
        nColNum=_nColNum;
        nRowNum=_nRowNum;
        m_pMatrixElement =new PIXEL*[nRowNum];
        m_pMemoryBase=new PIXEL [nRowNum*nColNum];
        PIXEL* p=m_pMemoryBase;
        for(int i=0;i<nRowNum;i++,p+=nColNum)
            m_pMatrixElement[i]=p;
        if(clear)
            memset(m_pMemoryBase,0,sizeof(PIXEL)*nRowNum*nColNum);
    }
}
//===============================================
void ZxImage::Clear(){
    memset(m_pMemoryBase,0,nColNum*nRowNum);
}
//===============================================
void ZxImage::SetTo(PIXEL value){
    for(int i=0;i<nRowNum;i++){
        for(int j=0;j<nColNum;j++){
            m_pMatrixElement[i][j]=value;
        }
    }
}
//===============================================
ZxMatrix::ZxMatrix(int _nRowNum,int _nColNum,bool clear){
    nColNum=_nColNum;
    nRowNum=_nRowNum;
    m_pMemoryBase=new float [nRowNum*nColNum];
    m_pMatrixElement=new float* [nRowNum];
    float* p=m_pMemoryBase;
    for(int i=0;i<nRowNum;i++,p+=nColNum){
        m_pMatrixElement[i]=p;
        if(clear)
            memset(m_pMemoryBase,0,sizeof (float)*nColNum);
    }
}
//===============================================
ZxMatrix::~ZxMatrix(){
    delete [] m_pMemoryBase;
    delete [] m_pMatrixElement;
}
//===============================================
ZxMatrix& ZxMatrix::operator=(ZxMatrix& operand){
    Resize(operand.nRowNum,operand.nColNum);
    for(int i=0;i<nRowNum;i++){
        for(int j=0;j<nColNum;j++){
            m_pMatrixElement[i][j]=operand.m_pMatrixElement[i][j];
        }
    }
    return *this;
}
//===============================================
ZxMatrix& ZxMatrix::operator+=(ZxMatrix& operand){
    for(int i=0;i<nRowNum;i++){
        for(int j=0;j<nColNum;j++){
            m_pMatrixElement[i][j]+=operand.m_pMatrixElement[i][j];
        }
    }
    return *this;
}
//===============================================
ZxMatrix& ZxMatrix::operator-=(ZxMatrix& operand){
    for(int i=0;i<nRowNum;i++){
        for(int j=0;j<nColNum;j++){
            m_pMatrixElement[i][j]-=operand.m_pMatrixElement[i][j];
        }
    }
    return *this;
}
//===============================================
ZxMatrix ZxMatrix::operator+(ZxMatrix& operand){
    ZxMatrix temp;
    if(nRowNum!=operand.nRowNum || nColNum!=operand.nColNum)
        return temp;
    temp.Resize(nRowNum,nColNum);
    for(int i=0;i<nRowNum;i++){
        for(int j=0;j<nColNum;j++){
            temp.m_pMatrixElement[i][j]=m_pMatrixElement[i][j]+operand.m_pMatrixElement[i][j];
        }
    }
    return temp;
}
//===============================================
ZxMatrix ZxMatrix::operator-(ZxMatrix& operand){
    ZxMatrix temp;
    if(nRowNum!=operand.nRowNum || nColNum!=operand.nColNum)
        return temp;

    for(int i=0;i<nRowNum;i++){
        for(int j=0;j<nColNum;j++){
            temp.m_pMatrixElement[i][j]=m_pMatrixElement[i][j]-operand.m_pMatrixElement[i][j];
        }
    }
    return temp;
}
//===============================================
ZxMatrix& ZxMatrix::operator+=(float scalar){
    for(int i=0;i<nRowNum;i++){
        for(int j=0;j<nColNum;j++){
            m_pMatrixElement[i][j]+=scalar;
        }
    }
    return *this;
}
//===============================================
ZxMatrix& ZxMatrix::operator-=(float scalar){
    for(int i=0;i<nRowNum;i++){
        for(int j=0;j<nColNum;j++){
            m_pMatrixElement[i][j]-=scalar;
        }
    }
    return *this;
}
//===============================================
ZxMatrix ZxMatrix::operator*(float scalar){
    ZxMatrix temp(nRowNum,nColNum);
    for(int i=0;i<nRowNum;i++){
        for(int j=0;j<nColNum;j++){
            temp.m_pMatrixElement[i][j]=m_pMatrixElement[i][j]*scalar;
        }
    }
    return temp;
}
//===============================================
ZxMatrix ZxMatrix::operator/(float scalar){
    ZxMatrix temp(nRowNum,nColNum);
    for(int i=0;i<nRowNum;i++){
        for(int j=0;j<nColNum;j++){
            temp.m_pMatrixElement[i][j]=m_pMatrixElement[i][j]/scalar;
        }
    }
    return temp;
}
//===============================================
void ZxMatrix::Clear(){
    memset(m_pMemoryBase,0,sizeof(float)*nColNum*nRowNum);
}
//===============================================
void ZxMatrix::Resize(int _nRowNum,int _nColNum,bool clear){
    if(nRowNum==_nRowNum &&nColNum==_nColNum){
        if(clear)
            Clear();
        return ;
    }else{
        delete [] m_pMemoryBase;
        delete [] m_pMatrixElement;
        nColNum=_nColNum;
        nRowNum=_nRowNum;
        m_pMatrixElement =new float*[nRowNum];
        m_pMemoryBase=new float [nRowNum*nColNum];
        float* p=m_pMemoryBase;
        for(int i=0;i<nRowNum;i++,p+=nColNum)
            m_pMatrixElement[i]=p;
        if(clear)
            memset(m_pMemoryBase,0,sizeof(float)*nRowNum*nColNum);
    }
}
//===============================================
ZxColorImage::ZxColorImage(int _nRowNum,int _nColNum){
    nColNum=_nColNum;
    nRowNum=_nRowNum;
    m_pMatrixElement.resize(_nRowNum);
   for(int i=0;i<_nRowNum;i++){
       m_pMatrixElement[i].resize(_nColNum);
       for(int j=0;j<_nColNum;j++){
           m_pMatrixElement[i][j].resize(3);
       }
   }
}
//===============================================
ZxColor::ZxColor(int _B,int _G,int _R){
    B=_B;
    G=_G;
    R=_R;
}
//===============================================
ZxColor ZxColor::operator()(int _B,int _G,int _R){
    B=_B;
    G=_G;
    R=_R;
}
//===============================================
ZxColor& ZxColor::operator=(ZxColor CopyColor){
    B=CopyColor.B;
    G=CopyColor.G;
    R=CopyColor.R;
    return *this;
}
//===============================================
void ZxColorImage::DrawPoint(ZxPoint pt,ZxColor color){
    m_pMatrixElement[pt.y][pt.x][0]=color.B;
    m_pMatrixElement[pt.y][pt.x][1]=color.G;
    m_pMatrixElement[pt.y][pt.x][2]=color.R;
}
//===============================================
void ZxColorImage::DrawLine(ZxPoint pt1,ZxPoint pt2,ZxColor color,float ThickNess){
    float len=pt1.Distance(pt2);
    ZxPoint unit_vec;
    unit_vec=(pt2-pt1)/len;
    float Current_len=0;

    float n_len=ThickNess/2;
    ZxPoint n_unit_vec(-unit_vec.y,unit_vec.x);
    ZxPoint nVec;
    float nCurrent_len=0;
    int x,y;
    while(Current_len<=len){
        if(ValidPoint(int(pt1.x),int(pt1.y))){
            m_pMatrixElement[(int) pt1.y][(int) pt1.x][0] = color.B;
            m_pMatrixElement[int(pt1.y)][int(pt1.x)][1] = color.G;
            m_pMatrixElement[int(pt1.y)][int(pt1.x)][2] = color.R;
        }
        nVec=n_unit_vec;
        nCurrent_len=0;
        while(nCurrent_len<n_len){
            y=(int)(pt1.y+nVec.y);
            x=(int)(pt1.x+nVec.x);
            if(ValidPoint(x,y)) {
                m_pMatrixElement[y][x][0] = color.B;
                m_pMatrixElement[y][x][1] = color.G;
                m_pMatrixElement[y][x][2] = color.R;
            }
            y=(int)(pt1.y-nVec.y);
            x=(int)(pt1.x-nVec.x);
            if(ValidPoint(x,y)) {
            m_pMatrixElement[y][x][0]=color.B;
            m_pMatrixElement[y][x][1]=color.G;
            m_pMatrixElement[y][x][2]=color.R;
            }
            nVec+=n_unit_vec;
            nCurrent_len++;
        }
        pt1+=unit_vec;
        Current_len++;
    }
}
//===============================================
bool ZxColorImage::ValidPoint(int x,int y){
    if(x>=0 && y>=0 && x<nColNum && y<nRowNum)
        return true;
    return false;
}
//===============================================
void ZxColorImage::DrawCircle(ZxPoint origin,float radius,ZxColor color,float ThickNess){
    ZxPoint Current(radius,0);
    float len=2*radius*Zx_Pi;
    ZxPoint nVec(-Current.y,Current.x);
    nVec = nVec/nVec.Norm();
    float Current_len=0;
    while(Current_len<=len){
        ZxPoint pt1=origin+Current;
        ZxPoint pt2=origin+Current+nVec;
        DrawLine(pt1,pt2,color,ThickNess);
        Current+=nVec;
        nVec(-Current.y,Current.x);
        nVec=nVec/nVec.Norm();
        Current_len++;
    }
}
//===============================================