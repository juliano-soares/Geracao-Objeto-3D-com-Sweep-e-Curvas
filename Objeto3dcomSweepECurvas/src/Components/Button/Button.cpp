/**
    Button functions
    @file Buttom.cpp
    @author Juliano Leonardo Soares
    @version 1.1 13/06/22
*/
#include "Button.hpp"
#include "../../Modules/gl_canvas2d.h"
#include "../../Utils/Utils.hpp"
#include <iostream>

using namespace std;

/* Constructor */
Button::Button(int id, int x, int y, float w, float h, vector<float> bg, const string label, vector<float> labelColor)
{
    this->x = x;
    this->y = y;
    this->width = w;
    this->height = h;
    this->bgColor = bg;
    this->label = label;
    this->labelColor = labelColor;
    this->id = id;
}

/* Renders/draws a button on the screen
 */
void Button::Render()
{
    CV::color(bgColor[0], bgColor[1], bgColor[2]);
    CV::rectFill(x, y, x + width, y + height);
    CV::color(labelColor[0], labelColor[1], labelColor[2]);
    // write the label of the button more or less in the center.
    float posX = (width - (label.length() * 10)) / 2;
    float posY = height / 2 - 5;
    CV::text(x + posX, y + posY, label.c_str());
}

/* Function responsible for checking the mouse position within the limits of the button.
   @param mouseX: X position in the mouse Cartesian.
   @param mouseY: Y position in the mouse Cartesian.
   @return a boolean if mouse is within button limits.
*/
bool Button::Collided(int mouseX, int mouseY)
{
    if (mouseX >= x && mouseX <= (x + width) && mouseY >= y && mouseY <= (y + height))
        return true;
    return false;
}

void Button::Hover(int mouseX, int mouseY)
{
    if (mouseX >= x && mouseX <= (x + width) && mouseY >= y && mouseY <= (y + height))
        bgColor = Utils::RGBtoFloat(255, 0, 0);
    else
        bgColor = Utils::RGBtoFloat(26, 35, 39);
}
