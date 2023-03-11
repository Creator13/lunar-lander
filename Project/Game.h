#pragma once

#include <cmath>
#include <stdio.h>
#include <SDL.h>
#include <SDL_opengl.h>

class Game
{
public:
    Game();

    void changeSize(int w, int h);
    void draw();

    void normalKeys(unsigned char key, int state);
    void specialKeys(int key, int state);
    void mouse(int button, int state, int x, int y);
    void mouseMotion(int x, int y);

    void initMtxFont();
    void draw_mtxText(float x, float y, const char* fmt, ...);
    void draw_mtxFont(float x, float y, Uint8 c);

    [[nodiscard]] float getWidth() const { return width; }
    [[nodiscard]] float getHeight() const { return height; }
    
private:
    float width, height;
    int counter;
    int mouseX, mouseY, mouseMotionX, mouseMotionY;
    int mouseButton, mouseState;

    char (*mtxFont)[7][5];
};
