#include "Point.hpp"
#include "../Modules/gl_canvas2d.h"
#include <cmath>
#include <iostream>

using namespace std;

Point::Point(){
    x = y = z = 0;
}

Point::Point(const Point & p){
    this->x = p.x;
    this->y = p.y;
    this->z = p.z;
}

Point::Point(double x, double y){
    this->x = x;
    this->y = y;
    this->z = 0;
}

Point::Point(double x, double y, double z){
    this->x = x;
    this->y = y;
    this->z = z;
}

void Point::RotateX(double ang){
    double temp = y;
    y = y*cos(ang) - z*sin(ang);
    z = temp*sin(ang) + z*cos(ang);
}

void Point::RotateY(double ang){
    double temp = x;
    x = x*cos(ang) + z*sin(ang);
    z = -temp*sin(ang) + z*cos(ang);
}

void Point::RotateZ(double ang){
    double temp = x;
    x = x*cos(ang) - y*sin(ang);
    y = temp*sin(ang) + y*cos(ang);
}

void Point::Translate(double x, double y, double z){
    this->x += x;
    this->y += y;
    this->z += z;
}

void Point::Projection(double d){
    this->x = (x*d) / z;
    this->y = (y*d) / z;
    this->z = 0;
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

    CV::circleFill(x, y, 4, 30);
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
{ }
