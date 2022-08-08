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
Curves::Curves(int n, Point *p1, Point *p2)
{
    cpontos = n;
    this->p1 = p1;
    this->p2 = p2;
}

Curves::~Curves()
{
}

double fatorial(int n)
{
    double x = 1.0;
    for (int i = 1; i <= n; i++)
        x *= (double)i;
    return x;
}

double Ni(int n, int i)
{
    double a1 = fatorial(n);
    double a2 = fatorial(i);
    double a3 = fatorial(n - i);
    return a1 / (a2 * a3); // Ni
}

double Bernstein(int n, int i, double t)
{
    double ti = (t == 0.0 && i == 0) ? 1.0 : pow(t, i);              /* t^i */
    double tni = (n == i && t == 1.0) ? 1.0 : pow((1 - t), (n - i)); /* (1 - t)^i */
    return Ni(n, i) * ti * tni;                                      // Bases Bernstein
}

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
            double b = Bernstein(npts - 1, i, t);
            p->x += b * pcontrole[i]->x;
            p->y += b * pcontrole[i]->y;
        }

        pcurva.push_back(p);
    }
};
void Curves::Apply(int typeConnection)
{
    if (typeConnection == 2)
        RenderBezierCurve();

    if (typeConnection == 3)
        RenderBSplineCurve();
}

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

void Curves::RenderLinesBetweenPoints() {}

void Curves::render()
{
    glPointSize(2);
    CV::color(1, 0, 0);
    for (Point *p : this->pcurva)
    {
        CV::point(p->x, p->y);
    }
    glPointSize(4);
    CV::color(0, 0, 0);
    for (Point *p : this->pcontrole)
    {
        CV::point(p->x, p->y);
    }
    glPointSize(1);
}

double Curves::getX(double x)
{
    return (x > p1->x + 5 ? (x < p2->x - 5 ? x : p2->x - 5) : p1->x + 5);
}

double Curves::getY(double y)
{
    return (y > p1->y + 5 ? (y < p2->y - 5 ? y : p2->y - 5) : p1->y + 5);
}
