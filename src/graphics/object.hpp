#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>

namespace findit {

class Object {
public:
    Object(std::vector<float> vertices);
    ~Object();

    [[nodiscard]] GLuint get_vao();
    [[nodiscard]] int get_vertices_count();

private:
    glm::vec3 m_position;
    glm::vec3 m_color;

    int m_vertices_count;

    GLuint m_VAO, m_VBO;
};

}