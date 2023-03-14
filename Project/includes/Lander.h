#pragma once
#include "glm/vec2.hpp"

using glm::vec2;

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
        vec2 position = vec2();

        float rotationDeg = 0;
        vec2 velocity = vec2();
    };
}
