#pragma once

#include <memory>
#include <SDL.h>

#include "FPSModule.h"
#include "Lander.h"

namespace LunarLander
{
    class Game
    {
    public:
        // Modules
        const std::unique_ptr<FPSModule> time;
        
        Game();

        // Graphics
        void changeSize(float newWidth, float newHeight);
        void update();
        void draw();

        // Input
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

        // Objects
        Lander lander;

        char (*mtxFont)[7][5];
    };
}
