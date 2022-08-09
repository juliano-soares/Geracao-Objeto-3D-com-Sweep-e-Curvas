/**
    Point functions
    @file Point.cpp
    @author Juliano Leonardo Soares
    @version 1.1 13/06/22
*/
#ifndef __POINT_H__
#define __POINT_H__

#pragma once

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
    Point(const Point &p);
    Point(double x, double y, double z);
    // Rotatations
    void RotateX(double ang);
    void RotateY(double ang);
    void RotateZ(double ang);
    // Translation
    void Translate(double x, double y, double z);
    // Other functions
    void circleInPoint();                    // draw circle
    void circleInPoint3d();                  // draw circle with smaller radius
    void pLineBold(Point &p2);               // draw filled line
    bool cIntersect(int mouseX, int mouseY); // calculate circle intersection
    void pLine(Point &p2);                   // draw line between points
    ~Point();
};
#endif
