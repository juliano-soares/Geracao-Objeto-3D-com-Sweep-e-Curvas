#ifndef MYMATRIX_H
#define MYMATRIX_H

#pragma once
class MyMatrix
{
    private:
        double m[3][3];
    public:
        MyMatrix();
        void forPoint(double &x, double &y);
        MyMatrix operator*(MyMatrix &);
        void identity();
        double& operator()(const unsigned &, const unsigned &);
        ~MyMatrix();
};

#endif
