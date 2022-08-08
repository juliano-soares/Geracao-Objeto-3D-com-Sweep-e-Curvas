#ifndef __OBJECT3D_H__
#define __OBJECT3D_H__

#include "../../Utils/Point.hpp"
#include "../../Utils/Utils.hpp"
#include "../Curves/Curves.hpp"
#pragma once

class Object3d
{
private:
    std::vector<std::vector<Point *>> malha;
    double animation;

public:
    double zang;
    double xang;
    int npontos;
    int nfaces;

    Object3d(int p, int f);
    void Apply(std::vector<Point *> pontos);
    void Render();
    void Moves(bool eixo, bool op, std::vector<Point *> pontos);

    void clear();

    ~Object3d();
};

#endif
