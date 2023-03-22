#pragma once

#include <memory>
#include <SDL.h>

#include "Ground.h"
#include "Lander.h"
#include "MtxFontRenderer.h"
#include "TimeModule.h"

namespace LunarLander
{
    class Game
    {
    public:
        inline static std::shared_ptr<MtxFontRenderer> fontRenderer = std::make_unique<MtxFontRenderer>();
        
        // Modules
        const std::unique_ptr<TimeModule> time;

        Game();

        // Game
        void update();
        void physics();
        
        // Graphics
        void changeSize(float newWidth, float newHeight);
        void draw() const;

        // Input
        void mouse(int button, int state, int x, int y);
        void mouseMotion(int x, int y);

        // Getters
        [[nodiscard]] float getWidth() const { return width; }
        [[nodiscard]] float getHeight() const { return height; }

    private:
        static constexpr uint32_t GROUND_HEIGHT = 575;
        
        float width, height;
        uint32_t mouseX = 0, mouseY = 0;
        uint32_t mouseMotionX = 0, mouseMotionY = 0;
        uint32_t mouseButton =0, mouseState = 0;

        // Objects
        Lander lander;
        Ground ground;
    };
}
