#include "FPSModule.h"
#include <SDL_timer.h>

using namespace LunarLander;


FPSModule::FPSModule(const uint32_t updateFrequency)
    : updateFrequency(updateFrequency)
{
    lastDeltaTimeUpdate = SDL_GetTicks();
    lastFrameTimeUpdate = SDL_GetTicks();
}


void FPSModule::tick()
{
    totalFrames++;

    updateDeltaTime();
    updateFrameTime();
}


void FPSModule::updateFrameTime()
{
    const uint32_t currentTime = SDL_GetTicks();
    framesSinceUpdate++;
    if (framesSinceUpdate >= updateFrequency)
    {
        frameTime = static_cast<float>(currentTime - lastFrameTimeUpdate) / static_cast<float>(framesSinceUpdate);
        framesSinceUpdate = 0;
        lastFrameTimeUpdate = SDL_GetTicks();
    }
}


void FPSModule::updateDeltaTime()
{
    const uint64_t deltaTimeMillis = lastDeltaTimeUpdate - SDL_GetTicks();
    deltaTime = static_cast<float>(deltaTimeMillis) / 1000.f;
    lastDeltaTimeUpdate = SDL_GetTicks();
}



