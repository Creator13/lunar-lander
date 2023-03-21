#include <iostream>
#include <SDL_opengl.h>

#include "Game.h"
#include "Input.h"

using namespace LunarLander;

Game game;

SDL_Window* window;

static void initAttributes()
{
    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);//Depth Buffer 24-bit
    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 4);
}

static void createSurface()
{
    SDL_Init(SDL_INIT_EVERYTHING);
    initAttributes(); //Context Attr
    window = SDL_CreateWindow("Lunar lander",
                              SDL_WINDOWPOS_UNDEFINED,
                              SDL_WINDOWPOS_UNDEFINED,
                              static_cast<int>(game.getWidth()), static_cast<int>(game.getHeight()),
                              SDL_WINDOW_OPENGL);
    SDL_GL_CreateContext(window);
    SDL_GL_SetSwapInterval(0);//Enable Vsync
    glEnable(GL_MULTISAMPLE);
}

static void mainLoop()
{
    SDL_Event event;
    bool quit = false;
    while (!quit)
    {
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
                //Mouse
                case SDL_MOUSEBUTTONDOWN:
                case SDL_MOUSEBUTTONUP:
                {
                    game.mouse((int)event.button.button,
                               (int)event.button.state,
                               (int)event.button.x,
                               (int)event.button.y);
                    break;
                }
                case SDL_MOUSEMOTION:
                {
                    game.mouseMotion((int)event.button.x,
                                     (int)event.button.y);
                    break;
                }
                //Keys
                case SDL_KEYDOWN:
                {
                    // Quit the game via pressing escape
                    if (event.key.keysym.sym == SDLK_ESCAPE)
                    {
                        quit = true;
                        break;
                    }                    
                    break;
                }
                // Quit the game natively (close window etc)
                case SDL_QUIT:
                {
                    quit = true;
                    break;
                }
                default: break;
            }
        }
        
        Input::updateKeyboardInput();

        game.update();
        game.physics();
        game.draw();
        
        SDL_GL_SwapWindow(window);
        // SDL_Delay(200);
    }
}

int main(int argc, char* argv[])
{
    createSurface();
    game.changeSize(game.getWidth(), game.getHeight());
    glClearColor(0.f, 0.f, 0.2f, 1.f);
    mainLoop();
    return 0;
}
