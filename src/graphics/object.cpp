#include "object.hpp"

namespace findit {

Object::Object(glm::vec3 color, glm::vec3 position, std::vector<float> vertices, std::shared_ptr<Logger> &logger) {
    m_logger = logger;
    m_vertices_count = vertices.size();
    m_color = color;

    m_position = position;
    for (int i = 0; i < vertices.size(); i+=3) {
        vertices[i] += m_position[0];
    }
    
    for (int i = 1; i < vertices.size(); i+=3) {
        vertices[i] += m_position[1];
    }

    for (int i = 2; i < vertices.size(); i+=3) {
        vertices[i] += m_position[2];
    }

    glGenVertexArrays(1, &m_VAO);
    glGenBuffers(1, &m_VBO);

    m_logger->log("[+] 'OBJECT' Generete buffers", m_logger->GREEN);

    glBindVertexArray(m_VAO);
    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float)*m_vertices_count, vertices.data(), GL_STATIC_DRAW);

    m_logger->log("[+] 'OBJECT' Set buffers data", m_logger->GREEN);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    m_logger->log("[+] 'OBJECT' Setup buffers", m_logger->GREEN);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    m_logger->log("[+] 'OBJECT' Unbind buffers", m_logger->GREEN);
}

Object::~Object() {
    glDeleteBuffers(1, &m_VBO);
    m_logger->log("[+] 'OBJECT' Delete VBO: " + std::to_string(m_VBO), m_logger->GREEN);

    glDeleteVertexArrays(1, &m_VAO);
    m_logger->log("[+] 'OBJECT' Delete VAO: " + std::to_string(m_VAO), m_logger->GREEN);
}

GLuint Object::get_vao() {
    return m_VAO;
}

glm::vec3 Object::get_color() {
    return m_color;
}

int Object::get_vertices_count() {
    return m_vertices_count;
}

}