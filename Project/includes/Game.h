#pragma once

#include <memory>
#include <SDL.h>

#include "FPSModule.h"
#include "Lander.h"
#include "MtxFontRenderer.h"

namespace LunarLander
{
    class Game
    {
    public:
        inline static std::shared_ptr<MtxFontRenderer> fontRenderer = std::make_unique<MtxFontRenderer>();
        
        // Modules
        const std::unique_ptr<FPSModule> time;

        Game();

        // Graphics
        void changeSize(float newWidth, float newHeight);
        void update();
        void draw() const;

        // Input
        void mouse(int button, int state, int x, int y);
        void mouseMotion(int x, int y);

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
    };
}
