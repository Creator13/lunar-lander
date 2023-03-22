#include "TimeModule.h"
#include <SDL_timer.h>

using namespace LunarLander;

TimeModule::TimeModule(const uint32_t updateFrequency)
    : updateFrequency(updateFrequency)
{
    lastDeltaTimeUpdate = SDL_GetTicks();
    lastFrameTimeUpdate = SDL_GetTicks();
}

void TimeModule::tick()
{
    totalFrames++;

    updateDeltaTime();
    updateFrameTime();
}

void TimeModule::updateFrameTime()
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

void TimeModule::updateDeltaTime()
{
    const uint64_t deltaTimeMillis = SDL_GetTicks() - lastDeltaTimeUpdate;
    deltaTime = static_cast<float>(deltaTimeMillis) / 1000.f;
    lastDeltaTimeUpdate = SDL_GetTicks();
}
