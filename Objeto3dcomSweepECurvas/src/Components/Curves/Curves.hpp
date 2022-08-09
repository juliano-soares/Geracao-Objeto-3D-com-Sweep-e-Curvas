/**
    Curves functions
    @file Curves.hpp
    @author Juliano Leonardo Soares
    @version 1.1 13/06/22
*/
#ifndef __CURVES_H__
#define __CURVES_H__

#include "../../Utils/Point.hpp"
#include "../../Utils/Utils.hpp"

#pragma once

class Curves
{
private:
    Point *p1;
    Point *p2;

public:
    vector<Point *> pcontrole; // vector of control points
    vector<Point *> pcurva;    // vector of curve points
    int cpontos;               // number of points on the curve

    void RenderBezierCurve();
    void RenderBSplineCurve();
    double getIntermediatePoints(int n, int i, double t);
    double recursiveLevels(int n, int i);
    double valuePoint(int n);
    Curves(int n, Point *p1, Point *p2);
    ~Curves();
    void render();
    void Apply(int typeConnection);
};
#endif
