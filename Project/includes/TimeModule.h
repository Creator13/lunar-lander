#pragma once
#include <cstdint>
#include <SDL_timer.h>

namespace LunarLander
{
    class TimeModule
    {
    public:
        explicit TimeModule(uint32_t updateFrequency);

        void tick();

        [[nodiscard]] float getFPS() const
        {
            return 1.f / (frameTime / 1000.f);
        }

        [[nodiscard]] float getFrameTime() const
        {
            return frameTime;
        }

        [[nodiscard]] uint32_t getCurrentFrame() const
        {
            return totalFrames;
        }

        [[nodiscard]] float getDeltaTime() const
        {
            return deltaTime;
        }

        [[nodiscard]] static float time()
        {
            return static_cast<float>(SDL_GetTicks()) / 1000.f;
        }

    private:
        const uint32_t updateFrequency = 500;

        float frameTime = 0;
        uint32_t totalFrames = 0;

        uint64_t lastFrameTimeUpdate = 0;
        uint64_t framesSinceUpdate = 0;

        float deltaTime = 0;
        uint32_t lastDeltaTimeUpdate = 0;

        void updateFrameTime();
        void updateDeltaTime();
    };
}
