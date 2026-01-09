#pragma once

#include <SDL3/SDL.h>

#define MOUSE_BUTTON_LEFT 0
#define MOUSE_BUTTON_RIGHT 1

namespace findit {

class Mouse {
public:
    Mouse() = default;

    [[nodiscard]] SDL_FPoint get_mouse_position();
    [[nodiscard]] SDL_FPoint get_mouse_rel();
    [[nodiscard]] bool is_mouse_down(bool side);
    [[nodiscard]] bool is_mouse_clicked_to_rect(SDL_Rect rect);

    void update_data(SDL_Event &event);
    void reset_relative();
private:
    SDL_FPoint m_old_position = {-1.0f, -1.0f};
    SDL_FPoint m_position = {-1.0f, -1.0f};
    SDL_FPoint m_rel;
    bool m_is_down_left;
    bool m_is_down_right;

};

}