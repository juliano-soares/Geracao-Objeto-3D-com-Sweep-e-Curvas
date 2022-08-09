/**
    Curves functions
    @file Curves.cpp
    @author Juliano Leonardo Soares
    @version 1.1 13/06/22
*/
#include "Curves.hpp"
#include "../../Modules/gl_canvas2d.h"
#include "../../Utils/Utils.hpp"
#include "../../Utils/Point.hpp"
#include <cmath>
#include <vector>
#include <iostream>

using namespace std;
/* Constructor */
Curves::Curves(int n, Point *p1, Point *p2)
{
    cpontos = n;
    this->p1 = p1;
    this->p2 = p2;
}

/* bézie curve - recursive functions to get the intermediate points, taken from youtube tutorials*/
double Curves::recursiveLevels(int n, int i)
{
    return valuePoint(n) / (valuePoint(i) * valuePoint(n - i));
}
double Curves::valuePoint(int n)
{
    double x = 1.0;
    for (int i = 1; i <= n; i++)
        x *= (double)i;
    return x;
}
double Curves::getIntermediatePoints(int n, int i, double t)
{
    double level1 = (t == 0.0 && i == 0) ? 1.0 : pow(t, i);
    double level2 = (n == i && t == 1.0) ? 1.0 : pow((1 - t), (n - i));
    return recursiveLevels(n, i) * level1 * level2;
}

/* function that stores the points of the bezier curves in an array for later rendering */
void Curves::RenderBezierCurve()
{
    int npts = pcontrole.size();
    double step = (double)1.0 / (cpontos - 1);
    double t = 0.0;

    pcurva.clear();
    for (int k = 0; k != cpontos; k++, t += step)
    {
        if ((1.0 - t) < 5e-6)
            t = 1.0;
        Point *p = new Point(0.0, 0.0, 0.0);
        for (int i = 0; i != npts; i++)
        {
            double b = getIntermediatePoints(npts - 1, i, t);
            p->x += b * pcontrole[i]->x;
            p->y += b * pcontrole[i]->y;
        }
        pcurva.push_back(p);
    }
};

/* function that stores the points of the B-Spline curves in an array for later rendering */
void Curves::RenderBSplineCurve()
{
    int npts = pcontrole.size();
    double step = (double)1.0 / (cpontos - 1);
    double t = 0.0;
    pcurva.clear();
    for (int k = 0; k != cpontos; k++, t += step)
    {
        if ((1.0 - t) < 5e-6)
            t = 1.0;
        Point *p = new Point(0.0, 0.0, 0.0);
        for (int i = 0; i != npts; i++)
        {
            p->x =
                (pcontrole[0]->x * ((1 - t) * (1 - t) * (1 - t))) +
                (pcontrole[1]->x * ((3 * (t * t * t)) - (6 * (t * t)) + 4)) +
                (pcontrole[2]->x * ((-3 * (t * t * t)) + (3 * (t * t)) + (3 * t) + 1)) +
                (pcontrole[3]->x * (t * t * t));
            p->x /= 6;
            p->y =
                (pcontrole[0]->y * ((1 - t) * (1 - t) * (1 - t))) +
                (pcontrole[1]->y * ((3 * (t * t * t)) - (6 * (t * t)) + 4)) +
                (pcontrole[2]->y * ((-3 * (t * t * t)) + (3 * (t * t)) + (3 * t) + 1)) +
                (pcontrole[3]->y * (t * t * t));
            p->y /= 6;
        }
        pcurva.push_back(p);
    }
}

/* function that applies the chosen curve type */
void Curves::Apply(int typeConnection)
{
    if (typeConnection == 1)
        RenderBezierCurve();
    if (typeConnection == 2)
        RenderBSplineCurve();
}

/* function renders the curves */
void Curves::render()
{
    for (Point *p : this->pcurva)
    {
        p->circleInPoint3d();
    }
    for (Point *p : this->pcontrole)
    {
        p->circleInPoint3d();
    }
}

Curves::~Curves()
{
    delete (p1);
    delete (p2);
}
