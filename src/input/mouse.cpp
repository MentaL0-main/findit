#include "mouse.hpp"

#include <SDL3/SDL.h>
#include <SDL3/SDL_mouse.h>
#include <stdexcept>

namespace findit {

SDL_FPoint Mouse::get_mouse_position() {
    return m_position;
}

SDL_FPoint Mouse::get_mouse_rel() {
    return m_rel;
}

bool Mouse::is_mouse_down(bool side) {
    if (side == MOUSE_BUTTON_LEFT) return m_is_down_left;
    if (side == MOUSE_BUTTON_RIGHT) return m_is_down_right;
    else throw std::runtime_error("[!] Error to is_mouse_down(): captured mouse button type. source: mouse.cpp");
}

bool Mouse::is_mouse_clicked_to_rect(SDL_Rect rect) {
    if (m_position.x > rect.x &&
        m_position.x < rect.x + rect.w &&
        m_position.y > rect.y &&
        m_position.y < rect.y + rect.h &&
        m_is_down_left) return true;
    
    return false;
}

void Mouse::update_data(SDL_Event &event) {
    m_old_position = m_position;
    SDL_GetMouseState(&m_position.x, &m_position.y);

    m_is_down_left = false;
    m_is_down_right = false;

    if (event.type == SDL_EVENT_MOUSE_BUTTON_DOWN) {
        if (event.button.button == SDL_BUTTON_LEFT) m_is_down_left = true;
        else if (event.button.type == SDL_BUTTON_RIGHT) m_is_down_right = true;
    }

    m_rel = {0.0f, 0.0f};
    SDL_GetRelativeMouseState(&m_rel.x, &m_rel.y);
}

}