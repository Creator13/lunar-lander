#include "Lander.h"

#include <iostream>
#include <SDL_opengl.h>

#include "Game.h"
#include "Input.h"
#include "LanderGraphics.h"
#include "glm/gtc/noise.hpp"
#include "glm/gtx/common.inl"
#include "glm/gtx/rotate_vector.hpp"
#include "glm/gtx/vector_angle.hpp"

using namespace LunarLander;
using glm::vec2;

// Default constructor
Lander::Lander() = default;

void Lander::init()
{
    rigidbody.mass = 750;
    rigidbody.position = vec2(100, 100);
    rigidbody.velocity = vec2(80, 0);
    actualRotation = -90;
    rotationInput = -90;
}

void Lander::draw() const
{
    glPushMatrix();
    glLoadIdentity();

    glLineWidth(.5f);
    glColor3ub(255, 255, 255);

    glTranslatef(rigidbody.position.x, rigidbody.position.y, 0);
    glRotatef(glm::fmod(actualRotation, 360.f), 0, 0, 1);
    glTranslatef(LANDER_SIZE * -.5f, LANDER_SIZE * -.5f, 0);

    DRAW_VERTS(Graphics::LANDER_BODY, GL_LINE_STRIP);
    DRAW_VERTS(Graphics::LANDER_BASE, GL_LINE_LOOP);
    DRAW_VERTS(Graphics::LANDER_EXHAUST, GL_LINE_STRIP);
    DRAW_VERTS(Graphics::LANDER_LEGS, GL_LINES);

    if (firePower > 0)
    {
        glPushMatrix();
        glTranslatef(0, (Graphics::BASE_HEIGHT * 2 + Graphics::BODY_SIZE) * LANDER_SIZE, 0);
        glScalef(1, firePower - glm::perlin(vec2(TimeModule::time() * 75.f, 0)) * .3f, 1);
        DRAW_VERTS(Graphics::LANDER_FLAME, GL_LINE_STRIP);
        glPopMatrix();
    }

    glPopMatrix();

    // Debug
    glPushMatrix();
    glTranslatef(rigidbody.position.x, rigidbody.position.y, 0);

    glColor3ub(255, 0, 0);

    glPointSize(2);
    glBegin(GL_POINTS);
    glVertex3f(0, 0, 0);
    glEnd();

    glPopMatrix();

    // Text
    glColor3ub(255, 255, 255);
    Game::fontRenderer->draw_mtxText(1000, 20, 1, "ALTITUDE: %4d", static_cast<int>(altitude));
    Game::fontRenderer->draw_mtxText(1000, 50, 1, "HOR. SPEED: %d", static_cast<int>(round(rigidbody.velocity.x)));
    Game::fontRenderer->draw_mtxText(1000, 80, 1, "VERT. SPEED: %d", static_cast<int>(round(rigidbody.velocity.y)));
}

void Lander::update(const float deltaTime)
{
    if (!enabled) return;
    
    // Rotation
    float dir = 0;
    if (Input::getLeftPressed() && !Input::getRightPressed())
        dir = -1;
    if (Input::getRightPressed() && !Input::getLeftPressed())
        dir = 1;

    // Clamp between -90 and 90 deg
    rotationInput = glm::clamp(rotationInput + dir * deltaTime * 100, -90.f, 90.f);

    // sticky around 0
    actualRotation = rotationInput;
    if (glm::abs(actualRotation) < 3.5)
    {
        actualRotation = 0;
    }

    // Force vec direction
    const vec2 rotated = glm::rotate(vec2(0, -1), glm::radians(actualRotation));

    // Firing
    if (Input::getFirePressed())
    {
        fireTime = glm::clamp(fireTime + deltaTime * 15, 0.f, 1.f);
        rigidbody.applyForce(rotated * maxFirePower);
    }
    else
    {
        fireTime = glm::clamp(fireTime - deltaTime * 15, 0.f, 1.f);
    }

    firePower = glm::smoothstep(0.f, 1.f, fireTime);

    // Update altitude
    altitude = static_cast<float>(Game::GROUND_HEIGHT) - rigidbody.position.y - Graphics::landerHeight();
}

void Lander::disable()
{
    enabled = false;
    fireTime = 0;
    firePower = 0;
}
