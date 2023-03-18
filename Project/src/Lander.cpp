#include "Lander.h"

#include <iostream>
#include <SDL_opengl.h>

#include "Game.h"
#include "Input.h"
#include "worldConstants.h"
#include "glm/gtx/common.inl"
#include "glm/gtx/rotate_vector.hpp"
#include "glm/gtx/vector_angle.hpp"

using namespace LunarLander;
using glm::vec2;

constexpr float SQUARE_SIZE = 20.f;

vec2 rotated;

Lander::Lander() : position(), velocity()
{
    init();
}

void Lander::init()
{
    position = vec2(100, 100);
    velocity = vec2(10, 0);
}

void Lander::draw() const
{
    glPushMatrix();
    glLoadIdentity();

    glLineWidth(2);
    glColor3ub(255, 255, 255);

    glTranslatef(position.x, position.y, 0);
    glRotatef(glm::fmod(actualRotation, 360.f), 0, 0, 1);
    glTranslatef(SQUARE_SIZE * -.5f, SQUARE_SIZE * -.5f, 0);

    glBegin(GL_LINE_LOOP);
    glVertex3f(.2f * SQUARE_SIZE, 0.f, 0);
    glVertex3f(SQUARE_SIZE * .8f, 0.f, 0);
    glVertex3f(SQUARE_SIZE, SQUARE_SIZE, 0);
    glVertex3f(0.f, SQUARE_SIZE, 0);
    glEnd();

    glPopMatrix();

    glPushMatrix();
    glTranslatef(position.x, position.y, 0);

    glColor3ub(255, 0,0);
    
    glBegin(GL_LINES);
    glVertex3f(0, 0, 0);
    glVertex3f(rotated.x * 40, rotated.y * 40, 0);
    glEnd();

    glPointSize(10);
    glBegin(GL_POINTS);
    glVertex3f(rotated.x * 40, rotated.y * 40, 0);
    glEnd();
    
    glPopMatrix();

    // Text
    Game::fontRenderer->draw_mtxText(1000, 20, "HOR. SPEED: %d", static_cast<int>(round(velocity.x)));
    Game::fontRenderer->draw_mtxText(1000, 50, "VERT. SPEED: %d", static_cast<int>(round(velocity.y)));
}

void Lander::update(const float deltaTime)
{
    float dir = 0;
    if (Input::getLeftPressed() && !Input::getRightPressed())
        dir = -1;
    if (Input::getRightPressed() && !Input::getLeftPressed())
        dir = 1;

    rotationInput = glm::clamp(rotationInput + dir * deltaTime * 100, -90.f, 90.f);
    
    actualRotation = rotationInput;
    if (glm::abs(actualRotation) < 3.5) actualRotation = 0;

    rotated = glm::rotate(vec2(0, -1), glm::radians(actualRotation));
    std::cout << "Rotated fire dir: x" << rotated.x << " y" << rotated.y << std::endl;

    if (Input::getFirePressed())
    {
        velocity += rotated * deltaTime * 100.f;
    }

    velocity += deltaTime * 15.f * World::GRAVITY;
    // std::cout << "velocity: x" << velocity.x << " y" << velocity.y << std::endl;
    position += deltaTime * velocity;
}
