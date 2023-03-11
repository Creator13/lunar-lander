#include "Lander.h"

#include <SDL_opengl.h>

using namespace LunarLander;

void Lander::init()
{
}

void Lander::draw() const
{
    glLineWidth(1);
    glBegin(GL_LINES);
    glEnd();
}

void Lander::update(const float deltaTime)
{
    
}

