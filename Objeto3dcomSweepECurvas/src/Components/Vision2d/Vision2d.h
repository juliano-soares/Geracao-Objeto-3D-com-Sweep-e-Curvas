#ifndef VISION2D_H
#define VISION2D_H

#include "../../Utils/Point.hpp"
#include "../../Utils/utils.h"
#include "../Curves/Curves.hpp"

class Vision2d
{
    Curves * curves;

    public:
        Vision2d();
        virtual ~Vision2d();
        void Render(vector<Point*> points, int typeConnection);

    protected:

    private:
};

#endif // VISION2D_H
