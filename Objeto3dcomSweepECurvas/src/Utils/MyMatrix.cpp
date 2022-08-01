#include "MyMatrix.hpp"
#include <cmath>

MyMatrix::MyMatrix()
{
    this->identity();
}

void MyMatrix::forPoint(double &x, double &y)
{
    double B[]{x, y, 1};
    double result[]{0, 0, 0};
    for (int i = 0; i < 3; i++)
    {
        for (int k = 0; k < 3; k++)
        {
            result[i] += this->m[i][k] * B[k];
        }
    }
    x = result[0];
    y = result[1];
}

MyMatrix MyMatrix::operator*(MyMatrix &B)
{
    MyMatrix result;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            result(i, j) = 0;
            for (int k = 0; k < 3; k++)
            {
                result(i, j) += m[i][k] * B(k, j);
            }
        }
    }

    return result;
}

void MyMatrix::identity()
{
    for (auto i = 0; i < 3; i++)
    {
        for (auto j = 0; j < 3; j++)
        {
            m[i][j] = i == j ? 1 : 0;
        }
    }
}

double &MyMatrix::operator()(const unsigned &lin, const unsigned &col)
{
    return this->m[lin][col];
}

MyMatrix::~MyMatrix()
{}
