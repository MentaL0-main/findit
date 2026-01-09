#include "controller.hpp"
#include "../input/keyboard.hpp"
#include "../input/mouse.hpp"

#include <glm/trigonometric.hpp>
#include <memory>

namespace findit {

void Controller::proccess(std::shared_ptr<Camera> &camera, 
                         std::shared_ptr<Keyboard> &keyboard, 
                         std::shared_ptr<Mouse> &mouse) {
    
    float mouseX = mouse->get_mouse_rel().x * m_sens;
    float mouseY = mouse->get_mouse_rel().y * m_sens;
    
    if (keyboard->is_key_down(SDL_SCANCODE_W)) camera->move_forward(m_speed);
    if (keyboard->is_key_down(SDL_SCANCODE_S)) camera->move_backward(m_speed);
    if (keyboard->is_key_down(SDL_SCANCODE_A)) camera->move_left(m_speed);
    if (keyboard->is_key_down(SDL_SCANCODE_D)) camera->move_right(m_speed);
    
    camera->rotate_y(mouseX * 2.0f);
    camera->rotate_x(-mouseY * 2.0f);
    
    camera->update();
}

}
