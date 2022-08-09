/**
    Object3d functions
    @file Object3d.cpp
    @author Juliano Leonardo Soares
    @version 1.1 24/07/22
*/
#include "../../Modules/gl_canvas2d.h"
#include "../../Utils/Utils.hpp"
#include "../../Utils/Point.hpp"
#include "Object3d.hpp"

#include <vector>
#include <iostream>

using namespace std;

/* constructor */
Object3d::Object3d(int p, int f)
{
    nPoints = p;
    nfaces = f;
}

/* function to rotate the point mesh */
void Object3d::Rotation(int eixo, bool op, std::vector<Point *> pontos)
{
    if (!wireframe.empty())
    {
        double step = op ? 0.01 : -0.01;
        if (eixo == 1)
            angX += step;
        if (eixo == 2)
            angY += step;
        if (eixo == 3)
            angZ += step;
        Apply(pontos);
    }
}

/* function to translate the mesh of points */
void Object3d::Translate(int eixo, bool op, std::vector<Point *> pontos)
{
    if (!wireframe.empty())
    {
        double step = op ? 10 : -10;
        if (eixo == 1)
            trX += step;
        if (eixo == 2)
            trY += step;
        Apply(pontos);
    }
}

/* function to apply changes to 3d object */
void Object3d::Apply(std::vector<Point *> pontos)
{

    for (auto vet : wireframe)
        vet.clear();
    wireframe.clear();

    double ang = 0.0;
    double step = PI_2 / nfaces;
    std::vector<Point *> pointsAux;

    for (int i = 0; i < nfaces; i++, ang += step)
    {
        pointsAux.clear();
        for (int j = 0; j < nPoints; j++)
        {
            pointsAux.push_back(new Point(*pontos[j]));
            pointsAux[j]->Translate(0, 0, 0);
            pointsAux[j]->RotateY(ang + angY);
            pointsAux[j]->RotateZ(angZ);
            pointsAux[j]->RotateX(angX);
            pointsAux[j]->Translate(620 + trX, 0 + trY, 0);
        }

        wireframe.push_back(pointsAux);
    }
}

/* function to render point mesh */
void Object3d::Render()
{
    if (!wireframe.empty())
    {
        CV::color(0, 0, 1);
        for (int j = 0; j < nPoints; j++)
        {
            for (int i = 0; i < nfaces; i++)
            {
                if (i == nfaces - 1)
                {
                    CV::line(wireframe[i][j]->x, wireframe[i][j]->y, wireframe[0][j]->x, wireframe[0][j]->y);
                    if (j != nPoints - 1)
                    {
                        CV::line(wireframe[i][j]->x, wireframe[i][j]->y, wireframe[i][j + 1]->x, wireframe[i][j + 1]->y);
                        CV::line(wireframe[i][j]->x, wireframe[i][j]->y, wireframe[0][j + 1]->x, wireframe[0][j + 1]->y);
                    }
                }
                else
                {
                    CV::line(wireframe[i][j]->x, wireframe[i][j]->y, wireframe[i + 1][j]->x, wireframe[i + 1][j]->y);
                    if (j != nPoints - 1)
                    {
                        CV::line(wireframe[i][j]->x, wireframe[i][j]->y, wireframe[i][j + 1]->x, wireframe[i][j + 1]->y);
                        CV::line(wireframe[i + 1][j + 1]->x, wireframe[i + 1][j + 1]->y, wireframe[i][j]->x, wireframe[i][j]->y);
                    }
                }
            }
        }

        CV::color(1, 0, 0);
        glPointSize(4);
        for (auto vet : wireframe)
        {
            for (auto p : vet)
            {
                CV::point(p->x, p->y);
            }
        }
        glPointSize(1);
    }
}

/* function to erase 3d objec */
void Object3d::reset()
{
    for (auto vet : wireframe)
        vet.clear();
    wireframe.clear();
    angZ = angX = angY = trX = trY = 0.0;
}
