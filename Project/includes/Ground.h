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
            // glm::vec2(-10, -30),
            // glm::vec2(40, -30),
            // glm::vec2(60, 0),
            // glm::vec2(160, 0),
            // glm::vec2(180, -20),
            // glm::vec2(200, -40),
            // glm::vec2(220, -45),
            // glm::vec2(260, -45),
            // glm::vec2(270, -35),
            // glm::vec2(290, -20),
            // glm::vec2(320, -15),
            // glm::vec2(360, -15),
            // glm::vec2(400, -60),
            // glm::vec2(420, 0),
            glm::vec2(1290, 0),
        };
        int zeroAltitude;
    };
}
