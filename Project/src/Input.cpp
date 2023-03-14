#include "Input.h"

#include <SDL_keyboard.h>

using namespace LunarLander;

void Input::updateKeyboardInput()
{
    const Uint8* keyState = SDL_GetKeyboardState(nullptr);

    isLeftPressed = keyState[SDL_SCANCODE_LEFT];
    isRightPressed = keyState[SDL_SCANCODE_RIGHT];
    isFirePressed = keyState[SDL_SCANCODE_SPACE] || keyState[SDL_SCANCODE_UP];
}
