#include "Lander.h"

#include <iostream>
#include <SDL_opengl.h>

using namespace LunarLander;

void Lander::init()
{
}

void Lander::draw() const
{
    glPushMatrix();
    glLoadIdentity();
    
    glLineWidth(2);
    glColor3ub(255, 255, 255);

    glTranslatef(position.x, position.y, 0);
    glScalef(50, 50, 1);
    
    glBegin(GL_LINE_STRIP);
    glVertex3f(0.f, 0.f, 0);
    glVertex3f(1.f, 0.f, 0);
    glVertex3f(1.f, 1.f, 0);
    glVertex3f(0.f, 1.f, 0);
    glVertex3f(0.f, 0.f, 0);
    glEnd();

    glPopMatrix();
}

void Lander::update(const float deltaTime)
{
    position += vec2(1, 1) * 10.f * deltaTime;
}

