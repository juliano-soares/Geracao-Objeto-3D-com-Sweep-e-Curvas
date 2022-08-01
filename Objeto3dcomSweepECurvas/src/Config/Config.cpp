#include "Config.h"
#include "../Modules/gl_canvas2d.h"
#include "../Utils/Utils.h"
#include "../Utils/Point.hpp"
#include "../Components/Button/Button.h"
#include "../Components/Checkbox/Checkbox.h"
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
    screenWidth = 1366;
    screenHeight = 720;
    v2d = new Vision2d();
    CreateButtons(v2d);
    CreateCheckbox(v2d);

    typeConnection = 0;
}

/* Renders/draws all components on the screen
*/
void Config::Render()
{
    renderAplication();

    for(vector<Point>::size_type i = 0; i != points.size(); i++)
        points[i]->circleInPoint();

    if(!points.empty())
        v2d->Render(points, typeConnection);

    for(vector<Button>::size_type i = 0; i != buttons.size(); i++)
        buttons[i]->Render();

    for(vector<Checkbox>::size_type i = 0; i != cbTypeConnection.size(); i++)
        cbTypeConnection[i]->Render();

    UpdateTypeConnection();
}

/*
    Init Canvas
*/
void Config::InitCanvas()
{
    CV::init(&screenWidth, &screenHeight, "T4 - Geração Objeto 3D com Sweep e Curvas");
    rgb = Utils::RGBtoFloat(20, 29, 43); // Background-color
    CV::clear(rgb[0], rgb[1], rgb[2]);
    CV::run();
}

/* Writes all texts on the screen
*/
void Config::renderAplication()
{
    // menu side bar
    rgb = Utils::RGBtoFloat(38, 49, 67);
    CV::color(rgb[0], rgb[1], rgb[2]);
    CV::rectFill(0, 0, screenWidth/2, 180);
    CV::rectFill(0, screenHeight, screenWidth, screenHeight - 30);

    // All texts
    rgb = Utils::RGBtoFloat(255, 250, 250);
    CV::color(rgb[0], rgb[1], rgb[2]);
    CV::text(screenWidth/2/2, screenHeight-20, "Visao 2D");
    CV::text(screenWidth/2 + screenWidth/2/2, screenHeight-20, "Visao 3D");
    CV::text(10, 160, "Tipo de conexao:");
    CV::text(10, 100, "Tipo de Bezier:");

    // Division lines
    CV::rectFill(screenWidth/2-1,0,screenWidth/2+1,screenHeight);
    CV::rectFill(0, screenHeight - 28, screenWidth, screenHeight - 30);

    CV::line(screenWidth/2/2, 180, screenWidth/2/2, screenHeight - 30);
}

//**********************************************************
//                                                        //
// Funções responsaveis pelas ações do usuário            //
//                                                        //
//**********************************************************

/* Function that receives keyboard input
   @params key: key value.
*/
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
            if(!points.empty())
                points.pop_back();
            break;
    }
};

/* Function that checks if the key has been released
   @params key: key value.
*/
void Config::keyboardUp(int key)
{
};

/* Function that checks mouse states
   @params button: button id.
   @params state: button state.
   @params wheel: mouse scroll.
   @params direction: mouse scroll direction.
   @params mouseX: mouse coordinate on the X axis.
   @params mouseY: mouse coordinate on the Y axis.
*/
void Config::Mouse(int button, int state, int wheel, int direction, int mouseX, int mouseY)
{
    // Verifica se o mouse esta na tela 2d
    if(mouseX > 0 && mouseX < screenWidth/2-1 && mouseY > 180 && mouseY < screenHeight - 30){
        insideCanvas = true;
    } else {
        insideCanvas = false;
    }

    for (vector<Button>::size_type i = 0; i != buttons.size(); i++){
        buttons[i]->Hover(mouseX, mouseY);
    }

    for (vector<Point>::size_type i = 0; i != points.size(); i++) {
        if(state == 0) {
            if(points[i]->cIntersect(mouseX, mouseY)) {
                interaction = true;
                pointSelectedId = i;
            }
        }
    }

    if (interaction && insideCanvas) {
        points[pointSelectedId]->x = mouseX;
        points[pointSelectedId]->y = mouseY;
    }

    if(state == 1 && interaction && insideCanvas) {
        points[pointSelectedId]->selected = false;
        pointSelectedId = NULL;
        interaction = false;
        return;
    }


    if(insideCanvas && state == 1 && !interaction) {
       points.push_back(new Point(mouseX, mouseY, 4));
       return;
    }

    if(state == 1) {
        isActivatedButton(mouseX, mouseY);
        isActivatedCheckbox(mouseX, mouseY, cbTypeConnection);
    }
}

//**********************************************************
//                                                        //
// Funções responsaveis pelos Botões                      //
//                                                        //
//**********************************************************

/* Function responsible for checking if the button was pressed.
   @param mouseX: X position in the mouse Cartesian.
   @param mouseY: Y position in the mouse Cartesian.
*/
void Config::isActivatedButton(int mouseX, int mouseY)
{
    for (vector<Button>::size_type i = 0; i != buttons.size(); i++){
        if(buttons[i]->Collided(mouseX, mouseY)) {
            ActionButton(buttons[i]);
        }
    }
}

/* Function responsible for triggering the action of the button.
   @param btn: object instance of button to be manipulated.
*/
void Config::ActionButton(Button* btn)
{
    if(btn->id == 1) // ID = Flip Vertical
        points.clear();
}

/* Function responsible for creating the buttons.
   @param img: object instance to be manipulated.
*/
void Config::CreateButtons(Vision2d* v2d)
{
    // Cores dos botoes
    vector<float> bg = Utils::RGBtoFloat(26,35,39);
    vector<float> labelColor = Utils::RGBtoFloat(255, 255, 255);

    // Flip
    buttons.push_back(new Button(&v2d, 1, 10, 10, 160, 30, bg, "Restaurar", labelColor));
}

//**********************************************************
//                                                        //
// Funções responsaveis pelos Checkbox                    //
//                                                        //
//**********************************************************

/* Function responsible for checking if the checkbox was pressed.
   @param mouseX: X position in the mouse Cartesian.
   @param mouseY: Y position in the mouse Cartesian.
*/
void Config::isActivatedCheckbox(int mouseX, int mouseY, vector<Checkbox*> cb)
{
    for (vector<Button>::size_type i = 0; i != cb.size(); i++){
        if(cb[i]->Collided(mouseX, mouseY)) {
            for (vector<Button>::size_type j = 0; j != cb.size(); j++)
                if(j != i)
                    cb[j]->isChecked = false;

            if(cb[i]->isChecked){
                cb[i]->isChecked = false;
            } else {
                cb[i]->isChecked = true;
            }
        }
    }
}

/* Function responsible for updating checkboxes.
*/
void Config::UpdateTypeConnection()
{
    if (!cbTypeConnection[0]->isChecked && !cbTypeConnection[1]->isChecked && !cbTypeConnection[2]->isChecked) {
        typeConnection = 0;
    }
    else {
        if (cbTypeConnection[0]->isChecked) typeConnection = 1;
        else if (cbTypeConnection[1]->isChecked) typeConnection = 2;
        else if (cbTypeConnection[2]->isChecked) typeConnection = 3;
        else typeConnection = 0;
    }
}

/* Function responsible for creating the checkboxes
   @param img: object instance to be manipulated.
*/
void Config::CreateCheckbox(Vision2d* v2d)
{
    vector<float> labelColor = Utils::RGBtoFloat(255, 250, 250);
    cbTypeConnection.push_back(new Checkbox(&v2d, 10, 120, 20, 20, false, "Retas", Utils::RGBtoFloat(255,99,71), Utils::RGBtoFloat(255,250,250)));
    cbTypeConnection.push_back(new Checkbox(&v2d, 110, 120, 20, 20, false, "Bezier", Utils::RGBtoFloat(50,205,50), Utils::RGBtoFloat(255,250,250)));
    cbTypeConnection.push_back(new Checkbox(&v2d, 220, 120, 20, 20, false, "Spline", Utils::RGBtoFloat(30,144,255), Utils::RGBtoFloat(255,250,250)));


    //checkboxes.push_back(new Checkbox(&v2d, 10, 60, 20, 20, false, "N-fatores (8)", Utils::RGBtoFloat(30,144,255), Utils::RGBtoFloat(255,250,250)));
    //checkboxes.push_back(new Checkbox(&v2d, 180, 60, 20, 20, false, "C^0", Utils::RGBtoFloat(30,144,255), Utils::RGBtoFloat(255,250,250)));
    //checkboxes.push_back(new Checkbox(&v2d, 270, 60, 20, 20, false, "C^1", Utils::RGBtoFloat(30,144,255), Utils::RGBtoFloat(255,250,250)));
    //checkboxes.push_back(new Checkbox(&v2d, 370, 60, 20, 20, false, "C^2", Utils::RGBtoFloat(30,144,255), Utils::RGBtoFloat(255,250,250)));
}
