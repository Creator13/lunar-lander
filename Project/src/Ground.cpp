#include "Ground.h"

#include <SDL_opengl.h>

using namespace LunarLander;

void Ground::draw() const
{
    glPushMatrix();
    glLoadIdentity();

    glLineWidth(1.f);
    glColor3ub(200, 200, 255);
    
    glTranslatef(0, static_cast<float>(zeroAltitude), 0);
    
    glBegin(GL_LINE_STRIP);
    for (const auto& vertex : vertices)
    {
        glVertex3f(vertex.x, vertex.y, 0);
    }
    glEnd();

    glPopMatrix();
}
