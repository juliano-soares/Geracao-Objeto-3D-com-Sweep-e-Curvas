/**
    Header MyMatrix
    @file Buttom.cpp
    @author Juliano Leonardo Soares
    @version 1.1 13/06/22
*/
#ifndef POSITION_H
#define POSITION_H

#include "MyMatrix.hpp"

#pragma once
class Point
{
private:
    MyMatrix mtx;

public:
    double x, y;
    int raio;
    bool selected;

    Point();
    Point(double x, double y, int raio);
    void rotate(double ang);              // apply the rotation
    void translate(double dx, double dy); // apply the translation
    void apply();                         // apply the transformations
    void scale(double sx, double sy);     // apply the scale

    void circleInPoint(); // desenha circulo
    void pLineBold(Point &p2);
    bool cIntersect(int mouseX, int mouseY); // calcula intersecção de círculo
    void pLine(Point &p2);                                           // desenha linha

    ~Point();
};
#endif
