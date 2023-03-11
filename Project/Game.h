#pragma once

#include <cmath>
#include <memory>
#include <stdio.h>
#include <SDL.h>
#include <SDL_opengl.h>

namespace Game2D
{
    class FPSModule;
}

namespace Game2D
{
    class Game
    {
    public:
        Game();

        void changeSize(float newWidth, float newHeight);
        void draw();

        void normalKeys(unsigned char key, int state);
        void specialKeys(int key, int state);
        void mouse(int button, int state, int x, int y);
        void mouseMotion(int x, int y);

        void initMtxFont() const;
        void draw_mtxText(float x, float y, const char* fmt, ...);
        void draw_mtxFont(float x, float y, Uint8 c) const;

        [[nodiscard]] float getWidth() const { return width; }
        [[nodiscard]] float getHeight() const { return height; }

    private:
        float width, height;
        uint64_t frameCounter;
        uint32_t mouseX, mouseY, mouseMotionX, mouseMotionY;
        uint32_t mouseButton, mouseState;

        std::shared_ptr<FPSModule> fpsModule;

        char (*mtxFont)[7][5];
    };
}
