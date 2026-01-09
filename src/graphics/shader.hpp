#pragma once

#include "../logger/logger.hpp"

#include <GL/glew.h>
#include <memory>
#include <string>

namespace findit {

class Shader {
public:
    Shader(const std::string &vs, const std::string &fs, std::shared_ptr<Logger> &logger);
    [[nodiscard]] GLuint get_id();

private:
    GLuint m_ID;

    std::shared_ptr<Logger> m_logger;
};

}