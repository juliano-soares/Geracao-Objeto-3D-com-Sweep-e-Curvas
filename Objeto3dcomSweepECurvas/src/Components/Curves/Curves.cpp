/**
    Curves functions
    @file Curves.cpp
    @author Juliano Leonardo Soares
    @version 1.1 13/06/22
*/
#include "Curves.hpp"
#include "../../Modules/gl_canvas2d.h"
#include "../../Utils/Utils.h"
#include <cmath>
#include <vector>

Curves::Curves()
{
}

/* Method to set debug mode
*/
void Curves::SetDebug(bool debug)
{
    Debug = debug;
}

/* method to render bezier curves
   @param p1: point 1.
   @param p2: point 2.
   @param p3: point 3.
   @param p4: point 4.
   @param filled: boolean field to inform if the curve must be filled.
   @param rgb: a color to fill the curve.
*/
void Curves::RenderBezierCurve(Point * p1, Point * p2, Point * p3, Point * p4, bool filled, vector<float> rgb)
{
    if(Debug){
       ShowDebug(p1, p2, p3, p4);
    }

    double t = 0.0;
    for (t = 0.0; t < 1.0; t += 0.0005)
    {
        double x =
            p1->x * (pow((1 - t), 3)) +
            p2->x * (3 * t * (pow((1 - t), 2))) +
            p3->x * (3 * t * t * (1 - t)) +
            p4->x * (t * t * t);

        double y =
            p1->y * (pow((1 - t), 3)) +
            p2->y * (3 * t * (pow((1 - t), 2))) +
            p3->y * (3 * t * t * (1 - t)) +
            p4->y * (t * t * t);

        if(filled){
            CV::color(rgb[0], rgb[1], rgb[2]);
            CV::line(x, y, x, -10);
        }

        CV::point(x, y);
    }
}

/* method to render B-Spline curves
   @param p1: point 1.
   @param p2: point 2.
   @param p3: point 3.
   @param p4: point 4.
*/
void Curves::RenderBSplineCurve(Point * p1, Point * p2, Point * p3, Point * p4)
{
    if(Debug){
       ShowDebug(p1, p2, p3, p4);
    }

    double t = 0.0;
    for (t = 0.0; t < 1.0; t += 0.0005)
    {
        double x =
            (p1->x * ((1 - t)*(1 - t)*(1 - t))) +
            (p2->x * ((3 * (t*t*t)) - (6 * (t * t)) + 4)) +
            (p3->x * ((-3 * (t*t*t)) + (3 * (t * t)) + (3 * t) + 1)) +
            (p4->x * (t * t * t));
        x /= 6;

        double y =
            (p1->y * ((1 - t)*(1 - t)*(1 - t))) +
            (p2->y * ((3 * (t*t*t)) - (6 * (t * t)) + 4)) +
            (p3->y * ((-3 * (t*t*t)) + (3 * (t * t)) + (3 * t) + 1)) +
            (p4->y * (t * t * t));
        y /= 6;

        CV::point(x, y);
    }
}

/* Method to paint curve points when debug mode is activated
   @param p1: point 1.
   @param p2: point 2.
   @param p3: point 3.
   @param p4: point 4.
*/
void Curves::ShowDebug(Point * p1, Point * p2, Point * p3, Point * p4)
{
    CV::color(0, 0, 1);
    CV::circleFill(p1->x, p1->y, 5, 20);
    CV::circleFill(p2->x, p2->y, 5, 20);
    CV::circleFill(p3->x, p3->y, 5, 20);
    CV::circleFill(p4->x, p4->y, 5, 20);
}
