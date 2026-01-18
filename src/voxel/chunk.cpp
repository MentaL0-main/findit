#include "chunk.hpp"
#include "voxel.hpp"
#include "../graphics/shader.hpp"

#include <glm/ext/vector_float3.hpp>
#include <vector>
#include <glm/glm.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <GL/glew.h>
#include <unordered_set>

namespace findit {

Chunk::Chunk() {
    init_voxels();

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
    update_visiblity();
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

void Chunk::init_voxels() {
    for (int x = 0; x < m_CHUNK_SIZE; ++x)
        for (int z = 0; z < m_CHUNK_SIZE; ++z) {
            for (int y = 0; y < m_CHUNK_SIZE; ++y) {
                Voxel vox = {
                    .position = glm::vec3{x, y, z},
                    .color = glm::vec3{0.6f, 0.4, 0.4},
                };
                m_voxels.push_back(std::move(vox));
            }
        }
}

bool Chunk::is_visible(const Voxel &vox) {
    std::vector<glm::vec3> adjacent_positions = {
        {vox.position.x - 1, vox.position.y, vox.position.z}, // left
        {vox.position.x + 1, vox.position.y, vox.position.z}, // right
        {vox.position.x, vox.position.y + 1, vox.position.z}, // up
        {vox.position.x, vox.position.y - 1, vox.position.z}, // down
        {vox.position.x, vox.position.y, vox.position.z + 1}, // front
        {vox.position.x, vox.position.y, vox.position.z - 1}  // back
    };

    for (const auto& pos : adjacent_positions) {
        if (m_voxel_positions.find(pos) != m_voxel_positions.end()) {
            return false;
        }
    }

    return true;
}



void Chunk::update_visiblity() {
    for (auto &vox : m_voxels) {
        vox.visible = is_visible(vox);
    }
}

Chunk::~Chunk() {
    glDeleteBuffers(1, &m_vbo);
    glDeleteVertexArrays(1, &m_vao);
}

}
