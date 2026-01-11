#pragma once

#include "../camera/camera.hpp"
#include "../input/keyboard.hpp"
#include "../input/mouse.hpp"

#include <glm/trigonometric.hpp>
#include <memory>

namespace findit {

class Controller {
public:
    void proccess(std::shared_ptr<Camera> &camera, 
                  std::shared_ptr<Keyboard> &keyboard, 
                  std::shared_ptr<Mouse> &mouse);

private:
    float m_speed = 0.1f;
    float m_sens = 0.002f;
    float m_pitch = 0.0f;
};

}
