#pragma once

#include "../logger/logger.hpp"

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <memory>

namespace findit {

class Object {
public:
    Object(std::vector<float> vertices, std::shared_ptr<Logger> &logger);
    ~Object();

    [[nodiscard]] GLuint get_vao();
    [[nodiscard]] int get_vertices_count();

private:
    glm::vec3 m_position;
    glm::vec3 m_color;

    int m_vertices_count;

    GLuint m_VAO, m_VBO;

    std::shared_ptr<Logger> m_logger;
};

}