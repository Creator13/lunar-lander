#include "Game.h"
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
    SDL_GL_SetSwapInterval(1);//Enable Vsync
}


static void createSurface()
{
    SDL_Init(SDL_INIT_EVERYTHING);
    initAttributes(); //Context Attr
    window = SDL_CreateWindow("GFX",
                               SDL_WINDOWPOS_UNDEFINED,
                               SDL_WINDOWPOS_UNDEFINED,
                               game.getWidth(), game.getHeight(),
                               SDL_WINDOW_OPENGL);
    SDL_GL_CreateContext(window);
}


static void mainLoop()
{
    SDL_Event event;
    bool quit = false;
    int key, state;
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
                    key = event.key.keysym.sym;
                    state = SDL_GetModState();

                    // Quit the game via pressing escape
                    if (key == SDLK_ESCAPE)
                    {
                        quit = true;
                        break;
                    }

                    if (key < 128)
                    {
                        game.normalKeys(key, state);
                    }
                    else
                    {
                        game.specialKeys(key, state);
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

        game.draw();
        SDL_GL_SwapWindow(window);
        SDL_Delay(8);
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
