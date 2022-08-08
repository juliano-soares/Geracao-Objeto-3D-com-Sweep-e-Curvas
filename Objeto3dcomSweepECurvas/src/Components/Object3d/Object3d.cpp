#include "../../Modules/gl_canvas2d.h"
#include "../../Utils/Utils.hpp"
#include "../../Utils/Point.hpp"
#include "Object3d.hpp"

#include <vector>
#include <iostream>

using namespace std;

Object3d::Object3d(int p, int f)
{
    npontos = p;
    nfaces = f;
    animation = 0.005;
}

void Object3d::Apply(std::vector<Point *> pontos)
{
    // LIMPA o que já existia na malha
    for (auto vet : malha)
        vet.clear();
    malha.clear();

    double ang = 0.0;
    double step = PI_2 / nfaces;
    // Reconstroi a malha
    std::vector<Point *> data; // auxiliar
    for (int i = 0; i < nfaces; i++, ang += step)
    {
        data.clear();
        for (int j = 0; j < npontos; j++)
        {
            data.push_back(new Point(*pontos[j]));
            // Operações sobre o Ponto
            data[j]->Translate(0, 0, 0);
            data[j]->RotateY(ang + yang);
            data[j]->RotateZ(zang);
            data[j]->RotateX(xang);
            data[j]->Translate(620 + trX, 0 + trY, 0);
        }

        malha.push_back(data);
    }
}

void Object3d::Moves(int eixo, bool op, std::vector<Point *> pontos)
{
    if (!malha.empty())
    {
        double step = op ? 0.01 : -0.01; // verifica se soma ou diminui
        if (eixo == 1)
            xang += step;
        if (eixo == 2)
            yang += step;
        if (eixo == 3)
            zang += step;
        Apply(pontos); // reconstroi a malha
    }
}

void Object3d::Translate(int eixo, bool op, std::vector<Point *> pontos)
{
    if (!malha.empty())
    {
        cout << "Here" << trX;
        double step = op ? 10 : -10; // verifica se soma ou diminui
        if (eixo == 1)
            trX += step;
        if (eixo == 2)
            trY += step;
        Apply(pontos); // reconstroi a malha
    }
}

void Object3d::Render()
{
    if (!malha.empty())
    {
        for (auto vet : malha)
        {
            for (auto p : vet)
            {
                p->Translate(-620, 0, 0);
                p->RotateZ(animation);
                p->Translate(620, 0, 0);
            }
        }

        for (int i = 0; i < nfaces; i++)
        {
            for (int j = 0; j < npontos; j++)
            {
                if (i == nfaces - 1)
                {
                    CV::line(malha[i][j]->x, malha[i][j]->y, malha[0][j]->x, malha[0][j]->y);
                    if (j != npontos - 1)
                    {
                        CV::line(malha[i][j]->x, malha[i][j]->y, malha[i][j + 1]->x, malha[i][j + 1]->y);
                    }
                }
                else
                {
                    CV::line(malha[i][j]->x, malha[i][j]->y, malha[i + 1][j]->x, malha[i + 1][j]->y);
                    if (j != npontos - 1)
                    {
                        CV::line(malha[i][j]->x, malha[i][j]->y, malha[i][j + 1]->x, malha[i][j + 1]->y);
                        CV::line(malha[i][j]->x, malha[i][j]->y, malha[i + 1][j + 1]->x, malha[i + 1][j + 1]->y);
                    }
                }
            }
        }

        CV::color(1, 0, 0);
        glPointSize(4);
        for (auto vet : malha)
        {
            for (auto p : vet)
            {
                CV::point(p->x, p->y);
            }
        }
        glPointSize(1);
    }
}

void Object3d::clear()
{
    for (auto vet : malha)
        vet.clear();
    malha.clear();

    zang = xang = yang = trX = trY = 0.0;
}
