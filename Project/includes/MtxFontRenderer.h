#pragma once
#include <SDL_stdinc.h>
#include <string>

class MtxFontRenderer
{
public:
    MtxFontRenderer();
    ~MtxFontRenderer();
    
    // Font
    void draw_mtxText(const float x, const float y, const uint32_t scale, const char* fmt, ...) const;
    static float getPixelWidth(const std::string& str, int scale);
private:
    void initMtxFont() const;
    void draw_mtxFont(const float x, const float y, const uint32_t scale, const Uint8 c) const;
    char (*mtxFont)[7][5] = new char[128][7][5];
};
