#pragma once

#include <GL/glew.h>
#include <string>

namespace findit {

class Shader {
public:
    Shader(const std::string &vs, const std::string &fs);
    [[nodiscard]] GLuint get_id();

private:
    GLuint m_ID;

};

}