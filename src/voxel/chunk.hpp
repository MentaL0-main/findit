#pragma once

#include "voxel.hpp"
#include "../graphics/shader.hpp"

#include <vector>
#include <GL/glew.h>
#include <memory>
#include <unordered_set>
#include <functional>

namespace std {
    template<> struct hash<glm::ivec3> {
        size_t operator()(glm::ivec3 const& v) const noexcept {
            uint64_t seed = 0;
            seed ^= std::hash<int>()(v.x) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
            seed ^= std::hash<int>()(v.y) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
            seed ^= std::hash<int>()(v.z) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
            return seed;
        }
    };
}


namespace findit {

struct Vec3Hash {
    std::size_t operator()(const glm::vec3& vec) const {
        std::size_t h1 = std::hash<float>()(vec.x);
        std::size_t h2 = std::hash<float>()(vec.y);
        std::size_t h3 = std::hash<float>()(vec.z);
        return h1 ^ (h2 << 1) ^ (h3 << 2);
    }
};

struct Vec3Equal {
    bool operator()(const glm::vec3& lhs, const glm::vec3& rhs) const {
        return lhs == rhs;
    }
};

class Chunk {
public:
    Chunk();

    void render(GLuint shaderID, glm::vec3 pos);
    void init_voxels();
    bool is_visible(const Voxel &vox);
    void update_visiblity();

    ~Chunk();

private:
    static constexpr short m_CHUNK_SIZE = 16;
	std::unordered_set<glm::vec3, Vec3Hash, Vec3Equal> m_voxel_positions;
    std::vector<Voxel> m_voxels;
    GLuint m_vao, m_vbo;
};

}
