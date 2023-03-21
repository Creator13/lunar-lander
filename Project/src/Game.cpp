//  (c) Mikael Fridenfalk
//  Template for use in the course:
//  Linear Algebra, Trigonometry and Geometry, 7.5 c
//  Uppsala University, Sweden

#include <SDL_opengl.h>

#include "Game.h"
#include "FPSModule.h"
#include "Transform.h"

using namespace LunarLander;

Game::Game()
    : time(std::make_unique<FPSModule>(10)),
      width(1280), height(720),
      ground(GROUND_HEIGHT)
{
    lander.init();
}

void Game::changeSize(const float newWidth, const float newHeight)
{
    width = newWidth;
    height = newHeight;

    // Reset Viewport
    glViewport(0, 0, static_cast<GLsizei>(width), static_cast<GLsizei>(height));
    glMatrixMode(GL_PROJECTION);

    // Reset The Projection Matrix
    glLoadIdentity();
    glOrtho(0.0, width, height, 0.0, -1.0, .0); // Create Ortho View (0,0 At Top Left)
    glMatrixMode(GL_MODELVIEW);

    // Reset The ModelView Matrix
    glLoadIdentity();
}

void Game::physics()
{
    const float dt = time->getDeltaTime();

    Transform& t = lander.transform;
    
    t.applyWorldForces();
    
    t.updateVelocity(dt);
    t.updatePosition(dt);
}

void Game::update()
{
    lander.update(time->getDeltaTime());
}

void Game::draw() const
{
    time->tick();

    // Clear
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

    lander.draw();
    ground.draw();

    // Text
    const float textXPos = width - 300;
    glColor3ub(255, 0, 0);
    fontRenderer->draw_mtxText(textXPos, height - 5 * 24,
                               "X = %4d  Y = %4d",
                               mouseX, mouseY);
    glColor3ub(100, 100, 220);
    fontRenderer->draw_mtxText(textXPos, height - 4 * 24,
                               "X = %4d  Y = %4d",
                               mouseMotionX, mouseMotionY);
    fontRenderer->draw_mtxText(textXPos, height - 3 * 24,
                               "TIME = %7u",
                               SDL_GetTicks());
    // draw_mtxText(textXPos, height - 2 * 24,
    //              "FRAME = %7u",
    //              fpsModule->getCurrentFrame());
    fontRenderer->draw_mtxText(textXPos, height - 2 * 24,
                               "FPS = %2d",
                               static_cast<int>(time->getFPS()));
    //printf("[ret = %u\n",ret););
    // printf("Tick: %d | Frametime: %.2fms | FPS: %2.0f\n", fpsModule->getCurrentFrame(), fpsModule->getFrameTime(), fpsModule->getFPS());
}

void Game::mouse(const int button, const int state, const int x, const int y)
{
    mouseButton = button;//SDL_BUTTON_LEFT/SDL_BUTTON_MIDDLE/SDL_BUTTON_RIGHT
    mouseState = state;//SDL_PRESSED/SDL_RELEASED
    mouseX = x;
    mouseY = y;
}

void Game::mouseMotion(const int x, const int y)
{
    mouseMotionX = x;
    mouseMotionY = y;
}
