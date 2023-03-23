#pragma once

#include <array>

#include "glm/vec2.hpp"

namespace LunarLander::Graphics
{
    using glm::vec2;

# define LANDER_SIZE 15.f

    constexpr float BODY_SIZE = 0.9f;
    constexpr float BODY_CHAMFER = 0.20f;

    constexpr float BASE_HEIGHT = 0.2f;
    constexpr float BASE_CHAMFER = 0.2f / 3.f;

    constexpr float EXHAUST_WIDTH = 1.f / 3.f;
    constexpr float FLAME_LENGTH = 1.f;

    constexpr float LEGS_HEIGHT = 0.4f;
    constexpr float LEGS_TOP_WDT = 2.f / 3.f;
    constexpr float LEGS_BASE = 0.3f;

    constexpr float landerHeight()
    {
        return LANDER_SIZE * (BODY_SIZE + BASE_HEIGHT + LEGS_HEIGHT) - LANDER_SIZE * .5f;
    }

    constexpr float landerLegsWidth()
    {
        return LANDER_SIZE + LEGS_BASE;
    }

    constexpr std::array LANDER_BODY
    {
        // Bottom left
        vec2(.5f - .5f * BODY_SIZE + BODY_CHAMFER       , BODY_SIZE),
        vec2(.5f - .5f * BODY_SIZE                      , BODY_SIZE - BODY_CHAMFER),
        // Top left
        vec2(.5f - .5f * BODY_SIZE                      , BODY_CHAMFER),
        vec2(.5f - .5f * BODY_SIZE + BODY_CHAMFER       , 0),
        // Top right
        vec2(.5f + .5f * BODY_SIZE - BODY_CHAMFER       , 0),
        vec2(.5f + .5f * BODY_SIZE                      , BODY_CHAMFER),
        // Bottom Right
        vec2(.5f + .5f * BODY_SIZE                      , BODY_SIZE - BODY_CHAMFER),
        vec2(.5f + .5f * BODY_SIZE - BODY_CHAMFER       , BODY_SIZE)
    };

    constexpr std::array LANDER_BASE
    {
        vec2(BASE_CHAMFER, BODY_SIZE),
        vec2(0, BASE_CHAMFER + BODY_SIZE),

        vec2(0, BASE_HEIGHT - BASE_CHAMFER + BODY_SIZE),
        vec2(BASE_CHAMFER, BASE_HEIGHT + BODY_SIZE),

        vec2(1 - BASE_CHAMFER, BASE_HEIGHT + BODY_SIZE),
        vec2(1, BASE_HEIGHT - BASE_CHAMFER + BODY_SIZE),

        vec2(1, BASE_CHAMFER + BODY_SIZE),
        vec2(1 - BASE_CHAMFER, BODY_SIZE),
    };

    constexpr std::array LANDER_EXHAUST
    {
        vec2(.5f - EXHAUST_WIDTH * .4f, 0 + BODY_SIZE + BASE_HEIGHT),
        vec2(.5f - EXHAUST_WIDTH * .55f, BASE_HEIGHT + BODY_SIZE + BASE_HEIGHT),
        vec2(.5f + EXHAUST_WIDTH * .55f, BASE_HEIGHT + BODY_SIZE + BASE_HEIGHT),
        vec2(.5f + EXHAUST_WIDTH * .4f, 0 + BODY_SIZE + BASE_HEIGHT),
    };

    constexpr std::array LANDER_FLAME
    {
        vec2(.5f - EXHAUST_WIDTH * .4f, 0),
        vec2(.5f - EXHAUST_WIDTH * .25f, FLAME_LENGTH * .6),
        vec2(.5f, FLAME_LENGTH),
        vec2(.5f + EXHAUST_WIDTH * .25f, FLAME_LENGTH * .6),
        vec2(.5f + EXHAUST_WIDTH * .4f, 0),
    };

    constexpr std::array LANDER_LEGS
    {
        // LEFT
        vec2(0.5f - LEGS_TOP_WDT * .5f  , 0 + BODY_SIZE + BASE_HEIGHT),
        vec2(0                          , LEGS_HEIGHT + BODY_SIZE + BASE_HEIGHT),

        vec2(-(LEGS_BASE * .5f)         , LEGS_HEIGHT + BODY_SIZE + BASE_HEIGHT),
        vec2(LEGS_BASE * .5f            , LEGS_HEIGHT + BODY_SIZE + BASE_HEIGHT),

        // RIGHT
        vec2(0.5f + LEGS_TOP_WDT * .5f  , 0 + BODY_SIZE + BASE_HEIGHT),
        vec2(1                          , LEGS_HEIGHT + BODY_SIZE + BASE_HEIGHT),

        vec2(1 - LEGS_BASE * .5f        , LEGS_HEIGHT + BODY_SIZE + BASE_HEIGHT),
        vec2(1 + LEGS_BASE * .5f        , LEGS_HEIGHT + BODY_SIZE + BASE_HEIGHT)
    };
}

#define DRAW_VERTS(Arr, Mode)                                   \
glBegin(Mode);                                                  \
for (const auto& vtx : (Arr)) {                                 \
    glVertex3f(vtx.x * LANDER_SIZE, vtx.y * LANDER_SIZE, 0);    \
}                                                               \
glEnd()
