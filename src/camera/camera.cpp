#include "camera.hpp"
#include <algorithm>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/trigonometric.hpp>

namespace findit {

Camera::Camera(int window_width, int window_height, std::shared_ptr<Logger> &logger) {
    m_logger = logger;

    m_projection = glm::perspective(glm::radians(45.0f),
                                    static_cast<float>(window_width) / static_cast<float>(window_height), 
                                    0.1f,
                                    100.0f);

    m_view = glm::lookAt(glm::vec3{0.0f, 1.0f, 9.0f},
                         glm::vec3{0.0f, 0.0f, 0.0f},
                         glm::vec3{0.0f, 1.0f, 0.0f});
    
    m_model = glm::mat4(1.0f);
}

void Camera::move_forward(float step) {
    m_position += m_forward * step;
    m_center += m_forward * step;
}

void Camera::move_backward(float step) {
    m_position += -m_forward * step;
    m_center += -m_forward * step;
}

void Camera::move_left(float step) {
    m_position += m_left * step;
    m_center += m_left * step;
}

void Camera::move_right(float step) {
    m_position += -m_left * step;
    m_center += -m_left * step;
}

void Camera::rotate_x(float angle) {
    m_pitch += angle;
    m_pitch = std::clamp(m_pitch, -1.55f, 1.55f);
    
    m_forward.x = cos(m_yaw) * cos(m_pitch);
    m_forward.y = sin(m_pitch);
    m_forward.z = sin(m_yaw) * cos(m_pitch);
    m_forward = glm::normalize(m_forward);
    
    m_left = glm::normalize(glm::cross(m_up, m_forward));
}

void Camera::rotate_y(float angle) {
    m_yaw += angle;
    
    m_forward.x = cos(m_yaw) * cos(m_pitch);
    m_forward.y = sin(m_pitch);
    m_forward.z = sin(m_yaw) * cos(m_pitch);
    m_forward = glm::normalize(m_forward);
    
    m_left = glm::normalize(glm::cross(m_up, m_forward));
}

void Camera::update() {
    m_center = m_position + m_forward;
    m_view = glm::lookAt(m_position, m_center, m_up);
}

void Camera::push(GLuint id) {
    glUseProgram(id);

    glUniformMatrix4fv(glGetUniformLocation(id, "uModel"),     1, GL_FALSE, glm::value_ptr(m_model));
    glUniformMatrix4fv(glGetUniformLocation(id, "uView"),      1, GL_FALSE, glm::value_ptr(m_view));
    glUniformMatrix4fv(glGetUniformLocation(id, "uProjection"), 1, GL_FALSE, glm::value_ptr(m_projection));
}

}