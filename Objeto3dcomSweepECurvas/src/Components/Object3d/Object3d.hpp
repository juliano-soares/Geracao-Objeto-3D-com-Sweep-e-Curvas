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
    bool isAnimation = true;

public:
    double xang;
    double yang;
    double zang;
    double trX, trY;

    int npontos;
    int nfaces;

    Object3d(int p, int f);
    void Apply(std::vector<Point *> pontos);
    void Render();
    void Moves(int eixo, bool op, std::vector<Point *> pontos);
    void Translate(int eixo, bool op, std::vector<Point *> pontos);

    void clear();

    ~Object3d();
};

#endif
