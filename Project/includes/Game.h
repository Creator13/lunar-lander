#pragma once

#include <cmath>
#include <memory>
#include <stdio.h>
#include <SDL.h>
#include <SDL_opengl.h>

#include "Lander.h"

namespace LunarLander
{
    class FPSModule;
}

namespace LunarLander
{
    class Game
    {
    public:
        Game();

        // Graphics
        void changeSize(float newWidth, float newHeight);
        void update();
        void draw();

        // Input
        void normalKeys(unsigned char key, int state);
        void specialKeys(int key, int state);
        void mouse(int button, int state, int x, int y);
        void mouseMotion(int x, int y);

        // Font
        void initMtxFont() const;
        void draw_mtxText(float x, float y, const char* fmt, ...);
        void draw_mtxFont(float x, float y, Uint8 c) const;

        // Getters
        [[nodiscard]] float getWidth() const { return width; }
        [[nodiscard]] float getHeight() const { return height; }

    private:
        float width, height;
        uint64_t frameCounter;
        uint32_t mouseX, mouseY, mouseMotionX, mouseMotionY;
        uint32_t mouseButton, mouseState;

        std::shared_ptr<FPSModule> fpsModule;

        // Objects
        Lander lander;

        char (*mtxFont)[7][5];
    };
}
