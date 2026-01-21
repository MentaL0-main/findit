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
    update_visiblity();

    glGenVertexArrays(1, &m_vao);
    glGenBuffers(1, &m_vbo);

    glBindVertexArray(m_vao);

    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(voxel_vertices), voxel_vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(0);
}

void Chunk::render(GLuint shaderID, glm::vec3 pos) {
    for (int i = 0; i < m_voxels.size(); ++i) {
        if (!m_voxels[i].visible) [[likely]] continue;
        glm::mat4 model = glm::translate(glm::mat4(1.0f), m_voxels[i].position);
        model = glm::translate(model, pos);

        glUniformMatrix4fv(glGetUniformLocation(shaderID, "uModel"), 1, GL_FALSE, glm::value_ptr(model));
        glUniform3fv(glGetUniformLocation(shaderID, "uObjectColor"), 1, glm::value_ptr(m_voxels[i].color));
        
        glBindVertexArray(m_vao);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        glBindVertexArray(0);
    }
}

void Chunk::init_voxels() {
    srand(time(NULL));
    m_voxel_positions.clear();
    
    for (int x = 0; x < m_CHUNK_SIZE; ++x) {
        for (int z = 0; z < m_CHUNK_SIZE; ++z) {
            for (int y = 0; y < m_CHUNK_SIZE; ++y) {
                float r = rand() % 100;
                Voxel vox = {
                    .position = glm::vec3{x, y, z},
                    .color = glm::vec3{r/100.0f, 0.4f, 0.4f},
                };
                m_voxels.push_back(std::move(vox));
                m_voxel_positions.insert(glm::vec3{x, y, z});
            }
        }
    }
}

bool Chunk::is_visible(const Voxel& vox) {
    glm::ivec3 pos(static_cast<int>(vox.position.x),
                   static_cast<int>(vox.position.y), 
                   static_cast<int>(vox.position.z));
    
    std::array<glm::ivec3, 6> dirs = {
        glm::ivec3(-1, 0, 0),   // left
        glm::ivec3(1, 0, 0),    // right  
        glm::ivec3(0, 1, 0),    // top
        glm::ivec3(0, -1, 0),   // bottom
        glm::ivec3(0, 0, 1),    // front
        glm::ivec3(0, 0, -1)    // back
    };
    
    for (const auto& dir : dirs) {
        glm::ivec3 neighbor = pos + dir;
        
        if (neighbor.x < 0 || neighbor.x >= m_CHUNK_SIZE ||
            neighbor.y < 0 || neighbor.y >= m_CHUNK_SIZE ||
            neighbor.z < 0 || neighbor.z >= m_CHUNK_SIZE) {
            return true;
        }
        
        if (m_voxel_positions.find(neighbor) == m_voxel_positions.end()) {
            return true;
        }
    }
    
    return false;
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
