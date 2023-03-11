#pragma once
#include "glm/vec2.hpp"

using glm::vec2;

namespace LunarLander
{
    class Lander
    {
    public:
        void draw() const;
        void init();
        void update(float deltaTime);

    private:
        float rotationDeg = 0;
        vec2 position = vec2();
        vec2 velocity = vec2();
    };
}
