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
    framesSinceUpdate++;
    if (framesSinceUpdate >= updateFrequency)
    {
        const uint32_t currentTime = SDL_GetTicks();
        frameTime = static_cast<float>(currentTime - lastFrameTimeUpdate) / static_cast<float>(framesSinceUpdate);
        framesSinceUpdate = 0;
        lastFrameTimeUpdate = currentTime;
    }
}

void FPSModule::updateDeltaTime()
{
    const uint64_t deltaTimeMillis = SDL_GetTicks() - lastDeltaTimeUpdate;
    deltaTime = static_cast<float>(deltaTimeMillis) / 1000.f;
    lastDeltaTimeUpdate = SDL_GetTicks();
}
