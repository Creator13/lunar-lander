#pragma once
#include <cstdint>

namespace LunarLander
{
    class FPSModule
    {
    public:
        explicit FPSModule(uint32_t updateFrequency);
        
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
