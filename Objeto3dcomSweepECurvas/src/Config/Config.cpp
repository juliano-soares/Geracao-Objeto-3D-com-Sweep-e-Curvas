#include "Config.hpp"
#include "../Modules/gl_canvas2d.h"
#include "../Utils/Utils.hpp"
#include "../Utils/Point.hpp"
#include "../Components/Button/Button.hpp"
#include "../Components/Checkbox/Checkbox.hpp"
#include "../Components/Curves/Curves.hpp"
#include "../Components/Object3d/Object3d.hpp"

#include <iostream>
#include <algorithm>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <GL/glut.h>
#include <GL/freeglut_ext.h>
#include <sstream>

using namespace std;

Config::~Config() {}

/* Start the settings */
Config::Config()
{
    interaction = false;
    CreateButtons();
    CreateCheckbox();
    typeConnection = 0;
    Point *p1 = new Point(0, 180, 0);
    Point *p2 = new Point(250, screenHeight - 20, 0);
    curva = new Curves(20, p1, p2);
    object3d = new Object3d(2, 10);
}

/* Renders/draws all components on the screen
 */
void Config::Render()
{
    CV::color(4);
    if (!curva->pcontrole.empty())
    {
        curva->render();
        object3d->Render();
    }

    renderAplication();

    if (cbTypeConnection[2]->isChecked && curva->pcontrole.size() > 4)
    {
        curva->pcontrole.erase(curva->pcontrole.begin() + 4, curva->pcontrole.end());
    }

    for (vector<Point>::size_type i = 0; i != curva->pcontrole.size(); i++)
        curva->pcontrole[i]->circleInPoint();

    if (curva->pcurva.size() > 0)
        object3d->Apply(curva->pcurva);

    for (vector<Button>::size_type i = 0; i != buttons.size(); i++)
        buttons[i]->Render();

    for (vector<Checkbox>::size_type i = 0; i != cbTypeConnection.size(); i++)
        cbTypeConnection[i]->Render();

    curva->Apply(typeConnection);
    UpdateTypeConnection();
}

/* Init Canvas */
void Config::InitCanvas()
{
    CV::init(&screenWidth, &screenHeight, "T4 - Gera��o Objeto 3D com Sweep e Curvas");
    rgb = Utils::RGBtoFloat(20, 29, 43); // Background-color
    CV::clear(rgb[0], rgb[1], rgb[2]);
    CV::run();
}

/* Writes all texts on the screen */
void Config::renderAplication()
{
    // menu side bar
    rgb = Utils::RGBtoFloat(38, 49, 67);
    CV::color(rgb[0], rgb[1], rgb[2]);
    CV::rectFill(0, 0, screenWidth, 180);

    // All texts
    rgb = Utils::RGBtoFloat(255, 250, 250);
    CV::color(rgb[0], rgb[1], rgb[2]);
    CV::text(100, screenHeight - 20, "Visao 2D");
    CV::text(550, screenHeight - 20, "Visao 3D");
    CV::text(10, 160, "Tipo de conexao:");

    string nfaces = to_string(object3d->nfaces);
    string npontos = to_string(object3d->npontos);
    string string0 = "Num. Faces: " + nfaces + " Num. Pontos: " + npontos;
    CV::text(10, 90, string0.c_str());

    string rX = to_string(object3d->xang).substr(0, std::to_string(object3d->xang).find(".") + 2 + 1);
    string rY = to_string(object3d->yang).substr(0, std::to_string(object3d->yang).find(".") + 2 + 1);
    string rZ = to_string(object3d->zang).substr(0, std::to_string(object3d->zang).find(".") + 2 + 1);
    string string1 = "Rotacao: X: " + rX + " Y: " + rY + " Z: " + rZ;
    CV::text(10, 70, string1.c_str());

    string trX = to_string(object3d->trX).substr(0, std::to_string(object3d->trX).find(".") + 2 + 1);
    string trY = to_string(object3d->trY).substr(0, std::to_string(object3d->trY).find(".") + 2 + 1);
    string string2 = "Translacao: X: " + trX + " Y: " + trY;
    CV::text(10, 50, string2.c_str());

    CV::text(420, 160, "Teclas de acao:");
    CV::text(420, 140, "Faces: + [D] - [A] | Pontos: + [W] - [S]");
    CV::text(420, 120, "Apagar ultimo ponto: [BACKSPACE] | Todos pontos: [DELETE]");
    CV::text(420, 100, "Rotacao em X: + [4] - [6]");
    CV::text(420, 80, "Rotacao em Y: + [8] - [2]");
    CV::text(420, 60, "Rotacao em Z: + [7] - [9]");
    CV::text(420, 40, "Translacao em X: + [Seta Esquerda] - [Seta Direita]");
    CV::text(420, 20, "Translacao em Y: + [Seta Cima] - [Seta Baixo]");

    CV::rectFill(0, screenHeight - 28, screenWidth, screenHeight - 30);
    CV::line(252, 180, 252, screenHeight);
}

//**********************************************************
//                                                        //
// Fun��es responsaveis pelas a��es do usu�rio            //
//                                                        //
//**********************************************************

void Config::Keyboard(int key)
{
    cout << "\n"
         << key;
    if (key == 127) // Tecle'Delete' -> Limpar a Curva
    {
        curva->pcontrole.clear();
        curva->pcurva.clear();
        object3d->clear();
    }
    else if (key == 100) // Tecle'D' -> Adicionar Faces
    {
        object3d->nfaces++;
        object3d->Apply(curva->pcurva);
    }
    else if (key == 97)
    { // Tecle'A' -> Remover Faces
        object3d->nfaces = object3d->nfaces < 2 ? 1 : object3d->nfaces - 1;
        object3d->Apply(curva->pcurva);
    }
    else if (key == 119)
    { // Tecle'W" -> Adicionar Pontos
        curva->cpontos++;
        object3d->npontos++;
        curva->Apply(typeConnection);
        object3d->Apply(curva->pcurva);
    }
    else if (key == 115)
    { // Tecle'S' -> Remover Pontos
        curva->cpontos = curva->cpontos < 2 ? 1 : curva->cpontos - 1;
        object3d->npontos = object3d->npontos < 2 ? 1 : object3d->npontos - 1;
        curva->Apply(typeConnection);
        object3d->Apply(curva->pcurva);
    }
    else if (key == 8) // backspace -> apagar ultimo ponto
    {
        if (!curva->pcontrole.empty())
            curva->pcontrole.pop_back();
    }
    else if (key == 200) // Seta Esquerda -> Translada X para esquerda
        object3d->Translate(1, false, curva->pcurva);
    else if (key == 202) // Seta Direita -> Translada X para direita
        object3d->Translate(1, true, curva->pcurva);
    else if (key == 201) // Seta Cima -> Translada Y para cima
        object3d->Translate(2, true, curva->pcurva);
    else if (key == 203) // Seta Baixo -> Translada Y para baixo
        object3d->Translate(2, false, curva->pcurva);
    else if (key == 56) // Tecla 8 -> Rotaciona Y positivamente
        object3d->Moves(1, false, curva->pcurva);
    else if (key == 50) // Tecla 2 -> Rotaciona Y negativamente
        object3d->Moves(1, true, curva->pcurva);
    else if (key == 52) // Tecla 8 -> Rotaciona X positivamente
        object3d->Moves(2, false, curva->pcurva);
    else if (key == 54) // Tecla 8 -> Rotaciona X negativamente
        object3d->Moves(2, true, curva->pcurva);
    else if (key == 57) // Tecla 8 -> Rotaciona Z positivamente
        object3d->Moves(3, false, curva->pcurva);
    else if (key == 55) // Tecla 8 -> Rotaciona Z negativamente
        object3d->Moves(3, true, curva->pcurva);
};

void Config::keyboardUp(int key){};

/* Function that checks mouse states */
void Config::Mouse(int button, int state, int wheel, int direction, int mouseX, int mouseY)
{
    // Verifica se o mouse esta na tela 2d
    if (mouseX > 0 && mouseX < 250 && mouseY > 180 && mouseY < screenHeight - 30)
    {
        insideCanvas = true;
    }
    else
    {
        insideCanvas = false;
    }

    for (vector<Button>::size_type i = 0; i != buttons.size(); i++)
    {
        buttons[i]->Hover(mouseX, mouseY);
    }

    for (vector<Point>::size_type i = 0; i != curva->pcontrole.size(); i++)
    {
        if (state == 0)
        {
            if (curva->pcontrole[i]->cIntersect(mouseX, mouseY))
            {
                interaction = true;
                pointSelectedId = i;
            }
        }
    }

    if (interaction && insideCanvas)
    {
        curva->pcontrole[pointSelectedId]->x = mouseX;
        curva->pcontrole[pointSelectedId]->y = mouseY;
    }

    if (state == 1 && interaction && insideCanvas)
    {
        curva->pcontrole[pointSelectedId]->selected = false;
        pointSelectedId = -1;
        interaction = false;
        return;
    }

    if (insideCanvas && state == 1 && !interaction)
    {
        curva->pcontrole.push_back(new Point(mouseX, mouseY, 0));
        return;
    }

    if (state == 1)
    {
        isActivatedButton(mouseX, mouseY);
        isActivatedCheckbox(mouseX, mouseY, cbTypeConnection);
    }
}

//**********************************************************
//                                                        //
// Fun��es responsaveis pelos Bot�es                      //
//                                                        //
//**********************************************************

/* Function responsible for checking if the button was pressed. */
void Config::isActivatedButton(int mouseX, int mouseY)
{
    for (vector<Button>::size_type i = 0; i != buttons.size(); i++)
    {
        if (buttons[i]->Collided(mouseX, mouseY))
        {
            ActionButton(buttons[i]);
        }
    }
}

/* Function responsible for triggering the action of the button. */
void Config::ActionButton(Button *btn)
{
    if (btn->id == 1) {
        curva->pcontrole.clear();
        curva->pcurva.clear();
        object3d->clear();
    }
}

/* Function responsible for creating the buttons.*/
void Config::CreateButtons()
{
    vector<float> bg = Utils::RGBtoFloat(26, 35, 39);
    vector<float> labelColor = Utils::RGBtoFloat(255, 255, 255);
    buttons.push_back(new Button(1, 10, 10, 160, 30, bg, "Restaurar", labelColor));
}

//**********************************************************
//                                                        //
// Fun��es responsaveis pelos Checkbox                    //
//                                                        //
//**********************************************************

/* Function responsible for checking if the checkbox was pressed. */
void Config::isActivatedCheckbox(int mouseX, int mouseY, vector<Checkbox *> cb)
{
    for (vector<Button>::size_type i = 0; i != cb.size(); i++)
    {
        if (cb[i]->Collided(mouseX, mouseY))
        {
            for (vector<Button>::size_type j = 0; j != cb.size(); j++)
                if (j != i)
                    cb[j]->isChecked = false;

            if (cb[i]->isChecked)
            {
                cb[i]->isChecked = false;
            }
            else
            {
                if (i == 2 && curva->pcontrole.size() < 4)
                {
                    cb[i]->isChecked = false;
                    cout << "\nNumero de Pontos para B-Spline deve ser no minimo 4!! \n";
                }
                else
                {
                    cb[i]->isChecked = true;
                }
            }
        }
    }
}

/* Function responsible for updating checkboxes.
 */
void Config::UpdateTypeConnection()
{
    if (!cbTypeConnection[0]->isChecked && !cbTypeConnection[1]->isChecked && !cbTypeConnection[2]->isChecked)
    {
        typeConnection = 0;
    }
    else
    {
        if (cbTypeConnection[0]->isChecked)
            typeConnection = 1;
        else if (cbTypeConnection[1]->isChecked)
            typeConnection = 2;
        else if (cbTypeConnection[2]->isChecked)
            typeConnection = 3;
        else
            typeConnection = 0;
    }
}

/* Function responsible for creating the checkboxes
   @param img: object instance to be manipulated.
*/
void Config::CreateCheckbox()
{
    vector<float> labelColor = Utils::RGBtoFloat(255, 250, 250);
    cbTypeConnection.push_back(new Checkbox(10, 120, 20, 20, false, "Retas", Utils::RGBtoFloat(255, 99, 71), Utils::RGBtoFloat(255, 250, 250)));
    cbTypeConnection.push_back(new Checkbox(110, 120, 20, 20, false, "Bezier", Utils::RGBtoFloat(50, 205, 50), Utils::RGBtoFloat(255, 250, 250)));
    cbTypeConnection.push_back(new Checkbox(220, 120, 20, 20, false, "B-Spline", Utils::RGBtoFloat(30, 144, 255), Utils::RGBtoFloat(255, 250, 250)));
}
