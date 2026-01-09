#include "shader.hpp"
#include <stdexcept>

namespace findit {

Shader::Shader(const std::string &vs, const std::string &fs) {
    const char* vs_c_str = vs.c_str();
    const char* fs_c_str = fs.c_str();

    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vs_c_str, NULL);
    glCompileShader(vertexShader);
    
    GLint success;
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        GLint logLength;
        glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &logLength);
        
        GLchar* infoLog = new GLchar[logLength + 1];
        glGetShaderInfoLog(vertexShader, logLength, NULL, infoLog);
        
        std::string infoLogString = infoLog;
        delete[] infoLog;
        throw std::runtime_error("[!] Vertex shader compilation error: " + infoLogString);
    }

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fs_c_str, NULL);
    glCompileShader(fragmentShader);

    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        GLint logLength;
        glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &logLength);
        
        GLchar* infoLog = new GLchar[logLength + 1];
        glGetShaderInfoLog(fragmentShader, logLength, NULL, infoLog);
        
        std::string infoLogString = infoLog;
        delete[] infoLog;
        throw std::runtime_error("[!] Fragment shader compilation error: " + infoLogString);
        
    }

    m_ID = glCreateProgram();
    glAttachShader(m_ID, vertexShader);
    glAttachShader(m_ID, fragmentShader);
    glLinkProgram(m_ID);

    glLinkProgram(m_ID);
    GLint linkSuccess;
    glGetProgramiv(m_ID, GL_LINK_STATUS, &linkSuccess);
    if (!linkSuccess) {
        GLint logLength;
        glGetProgramiv(m_ID, GL_INFO_LOG_LENGTH, &logLength);
        
        GLchar* infoLog = new GLchar[logLength + 1];
        glGetProgramInfoLog(m_ID, logLength, NULL, infoLog);
        
        std::string infoLogString = infoLog;
        delete[] infoLog;
        throw std::runtime_error("Program link error: " + infoLogString);
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

GLuint Shader::get_id() {
    return m_ID;
}

}