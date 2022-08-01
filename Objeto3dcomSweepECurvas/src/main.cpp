/*
    Nome: Juliano Leonardo Soares
    Matricula: 201713854

    Descrição:

    Implementações:
    Básico:
        []
    Avançadas:
        []
    Melhorias a fazer:
    [ ]
*/
#include <GL/glut.h>
#include <GL/freeglut_ext.h> //callback da wheel do mouse.

#include "Config/Config.h"
#include <iostream>

using namespace std;

Config* config = new Config();

void render()
{
    config->Render();
}

void keyboard(int key)
{
    config->Keyboard(key);
}

void keyboardUp(int key)
{
   config->keyboardUp(key);;
}

void mouse(int button, int state, int wheel, int direction, int x, int y)
{
    config->Mouse(button, state, wheel, direction, x, y);
}

int main(int argc, char *argv[])
{
    config->InitCanvas();
}
