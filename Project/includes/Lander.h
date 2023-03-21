#pragma once

#include "Transform.h"

namespace LunarLander
{
    class Lander
    {
    public:
        Transform transform;
        
        Lander();

        void draw() const;

        // void physics();
        void update(float deltaTime);

        void init();

    private:
        float rotationInput = 0;
        float actualRotation = 0;
    };
}