#pragma once

#include "RigidBody.h"

namespace LunarLander
{
    class Lander
    {
    public:
        RigidBody rigidbody;

        Lander();

        void draw() const;

        // void physics();
        void update(float deltaTime);

        void init();

        void disable();

        [[nodiscard]] float getRotation() const { return actualRotation; }

    private:
        bool enabled = true;
        
        const float maxFirePower = 10000;

        float fireTime = 0;
        float firePower = 0;

        float rotationInput = 0;
        float actualRotation = 0;

        float altitude = 0;
    };
}
