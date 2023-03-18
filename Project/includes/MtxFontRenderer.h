#pragma once
#include <SDL_stdinc.h>

class MtxFontRenderer
{
public:
    MtxFontRenderer();
    ~MtxFontRenderer();
    
    // Font
    void draw_mtxText(float x, float y, const char* fmt, ...);

private:
    void initMtxFont() const;
    void draw_mtxFont(float x, float y, Uint8 c) const;
    char (*mtxFont)[7][5] = new char[128][7][5];
};
