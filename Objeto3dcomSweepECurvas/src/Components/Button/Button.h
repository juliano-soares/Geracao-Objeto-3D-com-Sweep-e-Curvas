/**
    Header Button
    @file Button.h
    @author Juliano Leonardo Soares
    @version 1.1 03/05/22
*/
#ifndef __BUTTON_H__
#define __BUTTON_H__

#include <string>
#include <vector>
#include "../Vision2d/Vision2d.h"

using namespace std;

class Button
{
public:
    int x, y;                   // initial positions
    int width, height;          // width and height
    int id;                     // button id

    Vision2d** v2d;     // ref to object
    vector<float> bgColor;      // background color
    string label;               // label
    vector<float> labelColor;   // label color

    Button();
    ~Button();
    Button(Vision2d** v2d, int id, int x, int y, float w, float h, vector<float> bg, const string label, vector<float> labelColor);
    void Render();
    bool Collided(int mx, int my);
    string_size_1(const string label);
    void Hover(int mouseX, int mouseY);
};

#endif

