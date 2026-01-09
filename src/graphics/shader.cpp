#include "shader.hpp"

#include <stdexcept>

namespace findit {

Shader::Shader(const std::string &vs, const std::string &fs, std::shared_ptr<Logger> &logger) {
    m_logger = logger;

    const char* vs_c_str = vs.c_str();
    const char* fs_c_str = fs.c_str();
    
    m_logger->log("[+] 'SHADER' Convert shaders source to C-String", m_logger->GREEN);

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
        throw std::runtime_error("[!] 'SHADER' Vertex shader compilation error: " + infoLogString);
    }

    m_logger->log("[+] 'SHADER' Compile vertex shader", m_logger->GREEN);


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
        throw std::runtime_error("[!] 'SHADER' Fragment shader compilation error: " + infoLogString);
        
    }

    m_logger->log("[+] 'SHADER' Compile fragment shader", m_logger->GREEN);

    m_ID = glCreateProgram();
    glAttachShader(m_ID, vertexShader);
    glAttachShader(m_ID, fragmentShader);
    glLinkProgram(m_ID);

    m_logger->log("[+] 'SHADER' Create shader program", m_logger->GREEN);

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
        throw std::runtime_error(" 'SHADER' Program link error: " + infoLogString);
    }

    m_logger->log("[+] 'SHADER' Link shader program", m_logger->GREEN);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    m_logger->log("[+] 'SHADER' Delete shaders", m_logger->GREEN);

}

GLuint Shader::get_id() {
    return m_ID;
}

}