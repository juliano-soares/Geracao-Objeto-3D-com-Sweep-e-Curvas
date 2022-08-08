#include "Config.hpp"
#include "../Modules/gl_canvas2d.h"
#include "../Utils/Utils.hpp"
#include "../Utils/Point.hpp"
#include "../Utils/Vector3.hpp"
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
    object3d = new Object3d(20, 100);
}

/* Renders/draws all components on the screen
 */
void Config::Render()
{
    renderAplication();
    CV::color(4);

    if(cbTypeConnection[2]->isChecked && curva->pcontrole.size() > 4) {
        curva->pcontrole.erase(curva->pcontrole.begin()+4, curva->pcontrole.end());
    }

    for (vector<Point>::size_type i = 0; i != curva->pcontrole.size(); i++)
        curva->pcontrole[i]->circleInPoint();


    if (!curva->pcontrole.empty())
    {
        curva->render();
        object3d->Render();
    }

    curva->Apply(typeConnection);
    if(curva->pcurva.size() > 0)
        object3d->Apply(curva->pcurva);

    for (vector<Button>::size_type i = 0; i != buttons.size(); i++)
        buttons[i]->Render();

    for (vector<Checkbox>::size_type i = 0; i != cbTypeConnection.size(); i++)
        cbTypeConnection[i]->Render();

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
    //CV::rectFill(0, screenHeight, screenWidth, screenHeight - 30);

    // All texts
    rgb = Utils::RGBtoFloat(255, 250, 250);
    CV::color(rgb[0], rgb[1], rgb[2]);
    CV::text(100, screenHeight - 20, "Visao 2D");
    CV::text(612, screenHeight - 20, "Visao 3D");
    CV::text(10, 160, "Tipo de conexao:");

    CV::rectFill(0, screenHeight - 28, screenWidth, screenHeight - 30);
    CV::line(screenWidth / 2 / 2, 180, 252, screenHeight);
}

//**********************************************************
//                                                        //
// Fun��es responsaveis pelas a��es do usu�rio            //
//                                                        //
//**********************************************************

void Config::Keyboard(int key)
{
    opcao = key;
    cout << key;
    switch (key)
    {
    case 27:
        exit(0);
        break;
    case 49:
        if (!curva->pcontrole.empty())
            curva->pcontrole.pop_back();
        break;
    }
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
    if (btn->id == 1) // ID = Flip Vertical
        curva->pcontrole.clear();
}

/* Function responsible for creating the buttons.*/
void Config::CreateButtons()
{
    // Cores dos botoes
    vector<float> bg = Utils::RGBtoFloat(26, 35, 39);
    vector<float> labelColor = Utils::RGBtoFloat(255, 255, 255);

    // Flip
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
                if(i == 2 && curva->pcontrole.size() < 4) {
                    cb[i]->isChecked = false;
                    cout << "\nNumero de Pontos para B-Spline deve ser no minimo 4!! \n";
                } else {
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