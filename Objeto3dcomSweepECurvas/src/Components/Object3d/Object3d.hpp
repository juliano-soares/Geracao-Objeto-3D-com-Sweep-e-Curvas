/**
    Object3d functions
    @file Object3d.hpp
    @author Juliano Leonardo Soares
    @version 1.1 24/07/22
*/
#ifndef __OBJECT3D_H__
#define __OBJECT3D_H__

#include "../../Utils/Point.hpp"
#include "../../Utils/Utils.hpp"
#include "../Curves/Curves.hpp"

#pragma once

class Object3d
{
private:
    std::vector<std::vector<Point *>> wireframe;

public:
    double angX, angY, angZ, trX, trY; // variables for rotation and translation
    int nPoints;
    int nfaces;

    Object3d(int p, int f);
    void reset();
    void Render();
    void Apply(std::vector<Point *> pontos);
    void Rotation(int eixo, bool op, std::vector<Point *> pontos);
    void Translate(int eixo, bool op, std::vector<Point *> pontos);
    ~Object3d();
};

#endif
