#ifndef __MYMATRIX_H__
#define __MYMATRIX_H__

#pragma once
class MyMatrix
{
private:
    double m[4][4];

public:
    MyMatrix();
    void forPoint(double &x, double &y, double &z);
    MyMatrix operator*(MyMatrix &);
    void identity();
    double &operator()(const unsigned &, const unsigned &);
    ~MyMatrix();
};

#endif
