#include "Transform.h"

#include "Extensions.h"
#include "WorldConstants.h"
#include "glm/detail/func_geometric.inl"

using namespace LunarLander;

void Transform::updateVelocity(const float dt)
{
    // a = m / F
    // v += a * dt
    velocity += 1.f / mass * force * dt;
    force = glm::zero<glm::vec2>();
}

void Transform::updatePosition(const float dt)
{
    // x += v * dt
    position += velocity * dt;
}

void Transform::applyForce(const glm::vec2& addForce)
{
    this->force += addForce;
}

void Transform::applyWorldForces()
{
    const glm::vec2 f_weight = mass * World::GRAVITY;
    const glm::vec2 f_drag = .5f * World::RESISTANCE * (velocity * velocity) * normalize(velocity);

    applyForce(f_weight - f_drag);
}
