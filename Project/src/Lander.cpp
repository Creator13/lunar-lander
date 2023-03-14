#include "Lander.h"

#include <iostream>
#include <SDL_opengl.h>

#include "Input.h"
#include "glm/gtx/common.inl"

using namespace LunarLander;

constexpr float SQUARE_SIZE = 40.f;

Lander::Lander()
{
    init();
}

void Lander::init()
{
    position = vec2(100, 100);
}

void Lander::draw() const
{
    glPushMatrix();
    glLoadIdentity();

    glLineWidth(2);
    glColor3ub(255, 255, 255);

    glTranslatef(position.x, position.y, 0);
    glRotatef(glm::fmod(rotationDeg, 360.f), 0, 0, 1);
    glTranslatef(SQUARE_SIZE * -.5f, SQUARE_SIZE * -.5f, 0);

    glBegin(GL_LINE_LOOP);
    glVertex3f(0.f, 0.f, 0);
    glVertex3f(SQUARE_SIZE, 0.f, 0);
    glVertex3f(SQUARE_SIZE, SQUARE_SIZE, 0);
    glVertex3f(0.f, SQUARE_SIZE, 0);
    glEnd();

    glPopMatrix();
}

void Lander::update(const float deltaTime)
{
    float dir = 0;
    if (Input::getLeftPressed() && !Input::getRightPressed())
        dir = -1;
    if (Input::getRightPressed() && !Input::getLeftPressed())
        dir = 1;

    rotationDeg+= dir * deltaTime * 100;

    // position += dir * 50 * deltaTime * vec2(1, 0) ;
}
