#ifndef __OBJECT3D_H__
#define __OBJECT3D_H__

#include "../../Utils/Point.hpp"
#include "../../Utils/Utils.hpp"
#include "../../Utils/Vector3.hpp"
#include "../Curves/Curves.hpp"
#include "../Graphics/Graphics.hpp"

#pragma once

class Object3d
{
private:
    std::vector<std::vector<Point *>> malha;
    double animation;
    bool isAnimation = true;

public:
    vector<Vec3f> vertices;
    double xang;
    double yang;
    double zang;
    double trX, trY;
    Graphics *g;

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
