#pragma once

#include <SDL3/SDL.h>

namespace findit {

class Keyboard {
public:
    Keyboard() = default;

    [[nodiscard]] bool is_key_down(SDL_Scancode code);
    [[nodiscard]] bool is_key_up(SDL_Scancode code);

};

}