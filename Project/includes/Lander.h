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
        const float maxFirePower = 13000;
        
        bool firing = false;
        float fire_t = 0;
        float firePower = 0;
        
        float rotationInput = 0;
        float actualRotation = 0;
    };
}
