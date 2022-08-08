#ifndef __CONFIG__H__
#define __CONFIG__H__

#include "../Components/Button/Button.hpp"
#include "../Components/Checkbox/Checkbox.hpp"
#include "../Components/Object3d/Object3d.hpp"
#include "../Components/Curves/Curves.hpp"
#include <vector>

using namespace std;

class Config
{
private:
    vector<float> rgb;
    int opcao = 50;
    int mouseX, mouseY;

public:
    int cliqueX = 0;
    int cliqueY = 0;
    int pointSelectedId;
    bool insideCanvas = false;
    bool interaction;

    int screenWidth = 1000;
    int screenHeight = 720;

    int difX, difY;
    int typeConnection;

    vector<Button *> buttons;
    vector<Checkbox *> cbTypeConnection;
    Curves *curva;
    Object3d *object3d;
    Point *m = NULL;

    Config();
    ~Config();

    // Function Canvas
    void InitCanvas();
    void Render();
    void renderAplication();

    // User Actions
    void Keyboard(int key);
    void keyboardUp(int key);
    void Mouse(int button, int state, int wheel, int direction, int mouseX, int mouseY);

    // Function Buttons
    void isActivatedButton(int mouseX, int mouseY);
    void ActionButton(Button *btn);
    void CreateButtons();
    void ChangeStateButtons();

    // Function Checkbox
    void isActivatedCheckbox(int mouseX, int mouseY, vector<Checkbox *> cb);
    void UpdateTypeConnection();
    void CreateCheckbox();
};

#endif
