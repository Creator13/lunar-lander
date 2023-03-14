#pragma once

namespace LunarLander
{
    class Input
    {
    public:
        static void updateKeyboardInput();
        
        [[nodiscard]] static bool getFirePressed() { return isFirePressed; }
        [[nodiscard]] static bool getRightPressed() { return isRightPressed; }
        [[nodiscard]] static bool getLeftPressed() { return isLeftPressed; }

    private:
        inline static bool isFirePressed = false, isLeftPressed = false, isRightPressed = false;
    };
}
