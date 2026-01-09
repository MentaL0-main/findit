#include "keyboard.hpp"

#include <SDL3/SDL.h>

namespace findit {

bool Keyboard::is_key_down(SDL_Scancode code) {
    return SDL_GetKeyboardState(NULL)[code];
}

bool Keyboard::is_key_up(SDL_Scancode code) {
    return !is_key_down(code);
}

}