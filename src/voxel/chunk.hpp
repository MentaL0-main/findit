#pragma once

#include "voxel.hpp"
#include "../graphics/shader.hpp"

#include <vector>
#include <GL/glew.h>
#include <memory.h>

namespace findit {

class Chunk {
public:
    Chunk(std::vector<Voxel> voxels);

    void render(GLuint shaderID);

    ~Chunk();

private:
    std::vector<Voxel> m_voxels;
    GLuint m_vao, m_vbo;
};

}
