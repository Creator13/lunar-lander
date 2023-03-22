#include "Lander.h"

#include <array>
#include <iostream>
#include <SDL_opengl.h>

#include "Game.h"
#include "Input.h"
#include "..\includes\LanderGraphics.h"
#include "MathExtras.h"
#include "glm/gtx/common.inl"
#include "glm/gtx/rotate_vector.hpp"
#include "glm/gtx/vector_angle.hpp"

using namespace LunarLander;
using glm::vec2;

vec2 rotated; //TODO remove

// Default constructor
Lander::Lander() = default;

void Lander::init()
{
    transform.mass = 750;
    transform.position = vec2(100, 100);
    transform.velocity = vec2(55, 0);
}

void Lander::draw() const
{
    glPushMatrix();
    glLoadIdentity();

    glLineWidth(.5f);
    glColor3ub(255, 255, 255);

    glTranslatef(transform.position.x, transform.position.y, 0);
    glRotatef(glm::fmod(actualRotation, 360.f), 0, 0, 1);
    glTranslatef(LANDER_SIZE * -.5f, LANDER_SIZE * -.5f, 0);

    DRAW_VECS(Graphics::LANDER_BODY, GL_LINE_STRIP);
    DRAW_VECS(Graphics::LANDER_BASE, GL_LINE_LOOP);
    DRAW_VECS(Graphics::LANDER_EXHAUST, GL_LINE_STRIP);
    DRAW_VECS(Graphics::LANDER_LEGS, GL_LINES);

    glPopMatrix();

    // Debug
    glPushMatrix();
    glTranslatef(transform.position.x, transform.position.y, 0);

    glColor3ub(255, 0, 0);

    float mag = -firePower * 40;
    
    glBegin(GL_LINES);
    glVertex3f(0, 0, 0);
    glVertex3f(rotated.x * mag, rotated.y * mag, 0);
    glEnd();

    glPointSize(10);
    glBegin(GL_POINTS);
    glVertex3f(rotated.x * mag, rotated.y * mag, 0);
    glEnd();

    glPopMatrix();

    // Text
    Game::fontRenderer->draw_mtxText(1000, 20, "HOR. SPEED: %d", static_cast<int>(round(transform.velocity.x)));
    Game::fontRenderer->draw_mtxText(1000, 50, "VERT. SPEED: %d", static_cast<int>(round(transform.velocity.y)));
}

void Lander::update(const float deltaTime)
{
    // Rotation
    float dir = 0;
    if (Input::getLeftPressed() && !Input::getRightPressed())
        dir = -1;
    if (Input::getRightPressed() && !Input::getLeftPressed())
        dir = 1;

    // Clamp between -90 and 90 deg
    rotationInput = glm::clamp(rotationInput + dir * deltaTime * 100, -90.f, 90.f);

    // sticky at 0
    actualRotation = rotationInput;
    if (glm::abs(actualRotation) < 3.5)
    {
        actualRotation = 0;
    }

    // Force vec direction
    rotated = glm::rotate(vec2(0, -1), glm::radians(actualRotation));

    // Firing
    if (Input::getFirePressed())
    {
        fire_t = glm::clamp(fire_t + deltaTime * 25, 0.f, 1.f);
    }
    else
    {
        fire_t = glm::clamp(fire_t - deltaTime * 25, 0.f, 1.f);
    }
    
    firePower = glm::smoothstep(0.f, 1.f, fire_t);

    if (firePower > 0)
    {
        transform.applyForce(rotated * firePower * maxFirePower);
    }
}
