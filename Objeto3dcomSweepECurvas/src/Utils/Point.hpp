/**
    Header MyMatrix
    @file Point.cpp
    @author Juliano Leonardo Soares
    @version 1.1 13/06/22
*/
#ifndef __POINT_H__
#define __POINT_H__

#include "MyMatrix.hpp"

#pragma once

#define degreesToRadians(angleDegrees) ((angleDegrees)*3.14 / 180.0)
#define radiansToDegrees(angleRadians) ((angleRadians)*180.0 / M_PI)

class Point
{
private:
public:
    double x, y, z;
    bool selected;
    int raio = 4;
    // Contructor
    Point();
    // Create
    Point(const Point & p);
    Point(double x, double y);
    Point(double x, double y, double z);
    // Rotatations
    void RotateX(double ang);
    void RotateY(double ang);
    void RotateZ(double ang);
    // Translation
    void Translate(double x, double y, double z);
    // Projection
    void Projection(double d);
    // ?????
    void circleInPoint(); // desenha circulo
    void pLineBold(Point &p2);
    bool cIntersect(int mouseX, int mouseY); // calcula intersecção de círculo
    void pLine(Point &p2);                   // desenha linha
    ~Point();
};
#endif
