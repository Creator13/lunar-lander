#pragma once
#include "glm/vec2.hpp"

namespace LunarLander
{
    class Lander
    {
    public:
        Lander();
        
        void draw() const;
        void init();
        void update(float deltaTime);

    private:
        glm::vec2 position;

        float rotationInput = 0;
        float actualRotation = 0;
        glm::vec2 velocity;
    };
}
