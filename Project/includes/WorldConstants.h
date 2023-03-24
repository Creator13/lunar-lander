#pragma once

#include "glm/vec2.hpp"

namespace LunarLander::World
{
    constexpr glm::vec2 GRAVITY = glm::vec2(0, 3 * 1.62f);
    constexpr float RESISTANCE = 2.5f;
}
