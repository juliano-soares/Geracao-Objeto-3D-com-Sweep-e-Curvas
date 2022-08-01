#include "Point.hpp"
#include "../Modules/gl_canvas2d.h"
#include <cmath>

#include <iostream>
using namespace std;

Point::Point() : mtx()
{
    x = y = 0;
}

Point::Point(double x, double y, int raio) : mtx()
{
    this->x = x;
    this->y = y;
    this->raio = raio;
    this->selected = false;
}

void Point::apply()
{
    mtx.forPoint(x, y);
    mtx.identity();
}

void Point::rotate(double ang)
{
    MyMatrix R;
    R(0, 0) = cos(ang);
    R(0, 1) = sin(ang);
    R(1, 0) = -sin(ang);
    R(1, 1) = cos(ang);
    mtx = mtx * R;
}

void Point::translate(double dx, double dy)
{
    MyMatrix T;
    T(0, 2) = dx;
    T(1, 2) = dy;
    mtx = mtx * T;
}

void Point::scale(double sx, double sy)
{
    MyMatrix S;
    S(0, 0) = sx;
    S(1, 1) = sy;
    mtx = mtx * S;
}

void Point::pLine(Point &p2)
{
    CV::line(x, y, p2.x, p2.y);
}

void Point::pLineBold(Point &p2)
{
    CV::line(x, y, p2.x, p2.y);
    CV::line(x-1, y-1, p2.x-1, p2.y-1);
    CV::line(x+1, y+1, p2.x+1, p2.y+1);
}

void Point::circleInPoint()
{
    if(selected) {
        CV::color(2);
    } else {
        CV::color(13);
    }

    CV::circleFill(x, y, raio, 30);
    CV::color(13);
}

bool Point::cIntersect(int mouseX, int mouseY)
{
    double d = sqrt((mouseX - x)*(mouseX - x)) + ((mouseY - y)*(mouseY - y));
    if (d > (raio + raio)) {
        return false;
    }
    selected = true;
    return true;
}

Point::~Point()
{
    delete &mtx;
}
