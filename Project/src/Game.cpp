//  (c) Mikael Fridenfalk
//  Template for use in the course:
//  Linear Algebra, Trigonometry and Geometry, 7.5 c
//  Uppsala University, Sweden

#include <SDL_opengl.h>

#include "Game.h"
#include "FPSModule.h"

using namespace LunarLander;

Game::Game()
    : time(std::make_unique<FPSModule>(10))
{
    mtxFont = new char[128][7][5];
    initMtxFont();

    frameCounter = 0;
    width = 1280;
    height = 720;
    mouseX = mouseY = 0;
    mouseMotionX = mouseMotionY = 0;
    mouseButton = mouseState = 0;

    lander = Lander();
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

void Game::update()
{
    lander.update(time->getDeltaTime());
}

void Game::draw()
{
    time->tick();

    // Clear
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

    // // Geometry
    // glLineWidth(3);
    // glPointSize(10);
    //
    // const int method[] = {GL_POINTS, GL_LINES, GL_LINE_STRIP, GL_LINE_LOOP, GL_POLYGON};
    //
    // for (int i = 0; i < 5; i++)
    // {
    //     glBegin(method[i]);
    //     const float dx = 200 + 220 * static_cast<float>(i);
    //     constexpr float dy = 350;
    //     glColor3ub(255, 0, 0);
    //     glVertex3f(-50 + dx, -50 + dy, 0);
    //     glColor3ub(127, 127, 0);
    //     glVertex3f(-50 + dx, 50 + dy, 0);
    //     glColor3ub(0, 255, 0);
    //     glVertex3f(50 + dx, 50 + dy, 0);
    //     glColor3ub(0, 0, 255);
    //     glVertex3f(50 + dx, -50 + dy, 0);
    //     glEnd();
    // }
    lander.draw();

    // Text
    const float textXPos = width - 300;
    glColor3ub(255, 0, 0);
    draw_mtxText(textXPos, height - 5 * 24,
                 "X = %4d  Y = %4d",
                 mouseX, mouseY);
    glColor3ub(100, 100, 220);
    draw_mtxText(textXPos, height - 4 * 24,
                 "X = %4d  Y = %4d",
                 mouseMotionX, mouseMotionY);
    draw_mtxText(textXPos, height - 3 * 24,
                 "TIME = %7u",
                 SDL_GetTicks());
    // draw_mtxText(textXPos, height - 2 * 24,
    //              "FRAME = %7u",
    //              fpsModule->getCurrentFrame());
    draw_mtxText(textXPos, height - 2 * 24,
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

// Font
void Game::initMtxFont() const
{
    for (int i = 0; i < 128; i++)
    {
        for (int j = 0; j < 7; j++)
        {
            for (int k = 0; k < 5; k++)
            {
                mtxFont[i][j][k] = 1;
            }
        }
    }

    constexpr char fontMap[] =
        "00000" "00000" "00000" "11111" "00000" "00000" "00000"//-
        "00000" "00000" "00000" "00000" "00000" "01100" "01100"//.
        "11111" "11111" "11111" "11111" "11111" "11111" "11111"//
        "01110" "10001" "10011" "10101" "11001" "10001" "01110"//0
        "00100" "01100" "00100" "00100" "00100" "00100" "01110"//1
        "01110" "10001" "00001" "00010" "00100" "01000" "11111"//2
        "01110" "10001" "00001" "00110" "00001" "10001" "01110"//3
        "00010" "00110" "01010" "10010" "11111" "00010" "00111"//4
        "11111" "10000" "11110" "00001" "00001" "10001" "01110"//5
        "01110" "10001" "10000" "11110" "10001" "10001" "01110"//6
        "11111" "10001" "00010" "00010" "00100" "00100" "00100"//7
        "01110" "10001" "10001" "01110" "10001" "10001" "01110"//8
        "01110" "10001" "10001" "01111" "00001" "00001" "01110"//9
        "00000" "01100" "01100" "00000" "01100" "01100" "00000"//:
        "11111" "11111" "11111" "11111" "11111" "11111" "11111"//
        "11111" "11111" "11111" "11111" "11111" "11111" "11111"//
        "00000" "00000" "11111" "00000" "11111" "00000" "00000"//=
        "11111" "11111" "11111" "11111" "11111" "11111" "11111"//
        "01110" "10001" "10001" "00010" "00100" "00000" "00100"//?
        "11111" "11111" "11111" "11111" "11111" "11111" "11111"//
        "01110" "10001" "10001" "11111" "10001" "10001" "10001"//A
        "11110" "10001" "10001" "11110" "10001" "10001" "11110"//B
        "01110" "10001" "10000" "10000" "10000" "10001" "01110"//C
        "11110" "10001" "10001" "10001" "10001" "10001" "11110"//D
        "11111" "10000" "10000" "11110" "10000" "10000" "11111"//E
        "11111" "10000" "10000" "11110" "10000" "10000" "10000"//F
        "01110" "10001" "10000" "10111" "10001" "10001" "01110"//G
        "10001" "10001" "10001" "11111" "10001" "10001" "10001"//H
        "01110" "00100" "00100" "00100" "00100" "00100" "01110"//I
        "00001" "00001" "00001" "00001" "10001" "10001" "01110"//J
        "10001" "10010" "10100" "11000" "10100" "10010" "10001"//K
        "10000" "10000" "10000" "10000" "10000" "10000" "11111"//L
        "10001" "11011" "10101" "10101" "10001" "10001" "10001"//M
        "10001" "10001" "11001" "10101" "10011" "10001" "10001"//N
        "01110" "10001" "10001" "10001" "10001" "10001" "01110"//O
        "11110" "10001" "10001" "11110" "10000" "10000" "10000"//P
        "01110" "10001" "10001" "10001" "10101" "10010" "01101"//Q
        "11110" "10001" "10001" "11110" "10100" "10010" "10001"//R
        "01111" "10000" "10000" "01110" "00001" "00001" "11110"//S
        "11111" "00100" "00100" "00100" "00100" "00100" "00100"//T
        "10001" "10001" "10001" "10001" "10001" "10001" "01110"//U
        "10001" "10001" "10001" "10001" "10001" "01010" "00100"//V
        "10001" "10001" "10001" "10101" "10101" "10101" "01010"//W
        "10001" "10001" "01010" "00100" "01010" "10001" "10001"//X
        "10001" "10001" "10001" "01010" "00100" "00100" "00100"//Y
        "11111" "00001" "00010" "00100" "01000" "10000" "11111";//Z

    for (int i = 0; i < 46; i++)
    {
        for (int j = 0; j < 7; j++)
        {
            for (int k = 0; k < 5; k++)
            {
                mtxFont[i + 45][j][k] = fontMap[35 * i + 5 * j + k];
            }
        }
    }
}

void Game::draw_mtxText(const float x, const float y, const char* fmt, ...)
{
    glPushMatrix();
    glLoadIdentity();

    char text[256];
    va_list ap;

    if (fmt == nullptr) return;

    va_start(ap, fmt);
#ifdef _WIN32 //32-bit and 64-bit Windows
    vsprintf_s(text, fmt, ap);
#else
    vsprintf(text, fmt, ap);
#endif
    va_end(ap);

    glPointSize(2.f);
    glBegin(GL_POINTS);
    int n = 0;
    while (text[n] != 0)
    {
        draw_mtxFont(x + 14.f * static_cast<float>(n), y, text[n]);
        n++;
    }

    glEnd();

    glPopMatrix();
}

void inline Game::draw_mtxFont(const float x, const float y, const Uint8 c) const
{
    if (c == ' ') return;

    for (int m = 0; m < 7; m++)
    {
        for (int n = 0; n < 5; n++)
        {
            if (mtxFont[c][m][n] == '0') continue;

            glVertex2f(x + 2 * static_cast<GLfloat>(n), y + 2 * static_cast<GLfloat>(m));
        }
    }
}
