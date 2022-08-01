#ifndef CURVES_H
#define CURVES_H

#include "../../Utils/Point.hpp"
#include "../../Utils/Utils.h"

#pragma once

class Curves{
    private:
        bool Debug;
    public:
        Curves();
        void RenderBezierCurve(Point * p1, Point * p2, Point * p3, Point * p4, bool filled, vector<float> rgb);
        void RenderBSplineCurve(Point * p1, Point * p2, Point * p3, Point * p4);
        void SetDebug(bool debug);
        void ShowDebug(Point * p1, Point * p2, Point * p3, Point * p4);
};
#endif
