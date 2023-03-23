//  (c) Mikael Fridenfalk
//  Template for use in the course:
//  Linear Algebra, Trigonometry and Geometry, 7.5 c
//  Uppsala University, Sweden

#include <SDL_opengl.h>

#include "Game.h"

#include <iostream>

#include "LanderGraphics.h"
#include "TimeModule.h"
#include "Transform.h"
#include "glm/gtx/rotate_vector.hpp"

using namespace LunarLander;

Game::Game()
    : time(std::make_unique<TimeModule>(10)),
      width(1280), height(720),
      ground(GROUND_HEIGHT)
{
    lander.init();
    gameState = Playing;
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
    time->tick();

    checkLanderCollision();

    if (gameState == Playing)
    {
        lander.update(time->getDeltaTime());

        physics();
    }
    draw();
}

void Game::draw() const
{
    // Clear
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

    ground.draw();
    if (gameState != Lost)
    {
        lander.draw();
    }

    // Text
    const float textXPos = width - 300;
    glColor3ub(255, 0, 0);
    fontRenderer->draw_mtxText(textXPos, height - 3 * 24, 1,
                               "TIME = %7u",
                               SDL_GetTicks());
    fontRenderer->draw_mtxText(textXPos, height - 2 * 24, 1,
                               "FPS = %4u",
                               static_cast<int>(time->getFPS()));

    // Lost/won
    glColor3ub(250, 250, 250);
    switch (gameState)
    {
        case Won:
            fontRenderer->draw_mtxText((getWidth() - MtxFontRenderer::getPixelWidth("won", 5)) * .5f, 300, 5, "WON");
            break;
        case Lost:
            fontRenderer->draw_mtxText((getWidth() - MtxFontRenderer::getPixelWidth("Lost", 5)) * .5f, 300, 5, "LOST");
            break;
        case Starting:
        case Playing:
            break;
    }
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

void Game::checkLanderCollision()
{
    using glm::vec2;
    auto leftLeg = vec2(-(Graphics::LEGS_BASE * .5f) * LANDER_SIZE - .5f * LANDER_SIZE, Graphics::landerHeight());
    auto rightLeg = vec2((1 + Graphics::LEGS_BASE * .5f) * LANDER_SIZE - .5f * LANDER_SIZE, Graphics::landerHeight());

    leftLeg = glm::rotate(leftLeg, glm::radians(lander.getRotation()));
    rightLeg = glm::rotate(rightLeg, glm::radians(lander.getRotation()));

    leftLeg += lander.transform.position;
    rightLeg += lander.transform.position;

    if (glm::max(leftLeg.y, rightLeg.y) > static_cast<float>(GROUND_HEIGHT))
    {
        if (length(lander.transform.velocity) < 7.5f && glm::abs(lander.getRotation()) < 15)
        {
            gameState = Won;
            lander.disable();
        }
        else
        {
            gameState = Lost;
        }
    }
}
