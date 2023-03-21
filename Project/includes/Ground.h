#pragma once
#include "glm/vec2.hpp"

namespace LunarLander
{
    class Ground
    {
    public:
        explicit Ground(const int position)
            : zeroAltitude(position) { }

        void draw() const;

    private:
        static constexpr glm::vec2 vertices[] =
        {
            glm::vec2(-10, 0),
            // vec2(-10, -30),
            // vec2(40, -30),
            // vec2(60, 0),
            // vec2(160, 0),
            // vec2(180, -20),
            // vec2(200, -40),
            // vec2(220, -45),
            // vec2(260, -45),
            // vec2(270, -35),
            // vec2(290, -20),
            // vec2(320, -15),
            // vec2(360, -15),
            // vec2(400, -60),
            // vec2(420, 0),
            glm::vec2(1290, 0),
        };
        int zeroAltitude;
    };
}
