#pragma once

#include "glm/vec2.hpp"
#include "glm/gtc/constants.hpp"

namespace LunarLander
{
    struct RigidBody
    {
        // Init an empty body with a mass and position (default to 1 and (0,0)) and a velocity of 0.
        explicit RigidBody(const float mass = 1, const glm::vec2 pos = glm::zero<glm::vec2>())
            : mass(mass),
              position(pos),
              velocity(glm::zero<glm::vec2>()) { }

        float mass;
        glm::vec2 position;
        glm::vec2 velocity;

        void updateVelocity(float dt);

        void updatePosition(float dt);

        void applyForce(const glm::vec2& addForce);

        void applyWorldForces();

    private:
        glm::vec2 force = glm::zero<glm::vec2>();
        glm::vec2 acceleration = glm::zero<glm::vec2>(); 
    };
}
