#include "chunk.hpp"
#include "voxel.hpp"
#include "../graphics/shader.hpp"

#include <vector>
#include <glm/glm.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <GL/glew.h>

namespace findit {

Chunk::Chunk(std::vector<Voxel> voxels) {
    m_voxels = voxels;

    glGenVertexArrays(1, &m_vao);
    glGenBuffers(1, &m_vbo);

    glBindVertexArray(m_vao);

    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(voxel_vertices), voxel_vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(0);
}

void Chunk::render(GLuint shaderID) {
    for (int i = 0; i < m_voxels.size(); ++i) {
        if (!m_voxels[i].visible) continue;

        glm::mat4 model = glm::translate(glm::mat4(1.0f), m_voxels[i].position);

        glUniformMatrix4fv(glGetUniformLocation(shaderID, "uModel"), 1, GL_FALSE, glm::value_ptr(model));
        glUniform3fv(glGetUniformLocation(shaderID, "uObjectColor"), 1, glm::value_ptr(m_voxels[i].color));
        
        glBindVertexArray(m_vao);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        glBindVertexArray(0);
    }
}

Chunk::~Chunk() {
}

}
