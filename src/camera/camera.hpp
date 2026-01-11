#pragma once

#include "../logger/logger.hpp"

#include <glm/glm.hpp>
#include <GL/glew.h>
#include <memory>

namespace findit {

class Camera {
public:
    Camera(int window_width, int window_height, std::shared_ptr<Logger> &logger);

    void push(GLuint id);
    void move_forward(float step);
    void move_backward(float step);
    void move_left(float step);
    void move_right(float step);
    void update();
    void rotate_x(float angle);
    void rotate_y(float angle);

private:
    glm::mat4 m_projection;
    glm::mat4 m_view;
    glm::mat4 m_model;

    glm::vec3 m_forward = glm::vec3{0.0f, 0.0f, -1.0f};
    glm::vec3 m_left = glm::vec3{-1.0f, 0.0f, 0.0f};

    glm::vec3 m_position = glm::vec3{0.0f, 1.8f, 0.0f};
    glm::vec3 m_center = glm::vec3{0.0f, 0.0f, 0.0f};
    glm::vec3 m_up = glm::vec3{0.0f, 1.0f, 0.0f};

    std::shared_ptr<Logger> m_logger;

    float m_yaw = -90.0f;
    float m_pitch = 0.0f;
};

}