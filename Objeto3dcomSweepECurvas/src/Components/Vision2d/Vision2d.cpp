#include "Vision2d.h"
#include "../../Utils/Point.hpp"

Vision2d::Vision2d()
{
    curves = new Curves();
}

Vision2d::~Vision2d()
{
    delete curves;
}

void Vision2d::Render(vector<Point*> points, int typeConnection)
{
    vector<float> rgb = Utils::RGBtoFloat(144, 191, 173);
    if(typeConnection == 1){
        for(vector<Point>::size_type i = 0; i != points.size() - 1; i++)
            points[i]->pLine(*points[i+1]);
    }
    if(typeConnection == 2) {
        curves->RenderBezierCurve(points[0],points[1],points[2],points[3], false, rgb);
    }

    if(typeConnection == 3) {
        curves->RenderBSplineCurve(points[0],points[1],points[2],points[3]);
    }
}
