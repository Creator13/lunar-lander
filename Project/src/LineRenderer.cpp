#include "LineRenderer.h"

#include <SDL_opengl.h>

#include "glm/vec2.hpp"

using namespace LunarLander;
using glm::vec2;

static void LineRenderer::drawLine(const vec2& begin, const vec2& end)
{
    glLineWidth(1);
    glBegin(GL_LINES);
    
    glVertex2f(begin.x, begin.y);
    glVertex2f(end.x, end.y);
    
    glEnd();
}