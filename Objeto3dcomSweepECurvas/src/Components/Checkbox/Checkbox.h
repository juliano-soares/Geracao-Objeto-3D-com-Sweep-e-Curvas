/**
    Header Checkbox
    @file Checkbox.h
    @author Juliano Leonardo Soares
    @version 1.1 03/05/22
*/
#ifndef __CHECKBOX_H__
#define __CHECKBOX_H__

#include <string>
#include <vector>
#include "../Vision2d/Vision2d.h"

using namespace std;

class Checkbox
{
public:
    Vision2d** v2d;             // object manipulated
    int  width, height;         // dimensions
    int x, y;                   // initial position
    bool isChecked;             // flag is checked
    string label;               // label
    vector<float> bgColor;      // background color
    vector<float> labelColor;   // label color

    Checkbox();
    ~Checkbox();
    Checkbox(Vision2d** v2d, int x, int y, float w, float h, bool isChecked, string label, vector<float> labelColor, vector<float> bg);
    void Render();
    bool Collided(int mouseX,int mouseY);
};

#endif

