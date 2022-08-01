#ifndef ___CONFIG__H___
#define ___CONFIG__H___

#include "../Components/Button/Button.h"
#include "../Components/Checkbox/Checkbox.h"
#include <vector>
#include <vector>
#include "../Vision2d/Vision2d.h"

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

    int screenWidth, screenHeight;
    int difX, difY;
    int typeConnection;

    vector<Button*> buttons;
    vector<Checkbox*> cbTypeConnection;
    vector<Checkbox*> cbTypeBeseir;
    vector<Point*> points;
    Vision2d *v2d;

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
    void ActionButton(Button* btn);
    void CreateButtons(Vision2d* v2d);
    void ChangeStateButtons(Vision2d* v2d);

    // Function Checkbox
    void isActivatedCheckbox(int mouseX, int mouseY, vector<Checkbox*> cb);
    void UpdateTypeConnection();
    void CreateCheckbox(Vision2d* v2d);
};

#endif
