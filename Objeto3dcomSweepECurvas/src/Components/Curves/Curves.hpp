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
    float knot[25];

public:
    vector<Point *> pcontrole; // vetor de pontos de controle
    vector<Point *> pcurva;    // vetor de pontos da curva
    int cpontos;               // quantidade de pontos na curva


    void RenderBezierCurve();
    void Casteljau(vector<Point *> ctrlPoints, double t, int n);
    void RenderBSplineCurve();
    double blend(vector<double> &uVec, double u, int k, int d);
    float CoxdeBoor(int i, int p, float t);
    void RenderLinesBetweenPoints();
    Curves(int n, Point *p1, Point *p2);
    ~Curves();
    void render();
    void Apply(int typeConnection);
    double getX(double x);
    double getY(double y);
};
#endif
