#include "../logger/logger.hpp"
#include "renderer.hpp"
#include "shader.hpp"

#include <SDL3/SDL.h>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <memory>
#include <stdexcept>

namespace findit {

Renderer::Renderer(SDL_GLContext &gl_contex, std::shared_ptr<Logger> &logger) {
    m_logger = logger;

    glewExperimental = GL_TRUE;
    GLenum err = glewInit();
    if (err != GLEW_OK) {
        std::cerr << "[!] 'RENDERER' ERROR: " << glewGetErrorString(err) << std::endl;
        throw std::runtime_error("[!] 'RENDERER' Failed to init glew");
    }

    m_logger->log("[+] 'RENDERER' Init glew", m_logger->GREEN);

    m_resource_manager = std::make_unique<ResourceManager>(m_logger);
    m_logger->log("[+] 'RENDERER' Create resource manager object", m_logger->GREEN);

    m_shader = std::make_unique<Shader>(m_resource_manager->loadShader("../assets/shaders/vertex.glsl"),
                                        m_resource_manager->loadShader("../assets/shaders/fragment.glsl"),
                                        m_logger);
    m_logger->log("[+] 'RENDERER' Create shader object", m_logger->GREEN);

    glEnable(GL_DEPTH_TEST);
    m_logger->log("[+] 'RENDERER' Enabled DEPTH_TEST", m_logger->GRAY);
}

void Renderer::set_clear_color(float r, float g, float b, float a) {
    glClearColor(r, g, b, a);
}

void Renderer::clear() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::present(SDL_Window* window) {
    SDL_GL_SwapWindow(window);
}

void Renderer::rectangle() {
    glBegin(GL_TRIANGLE_FAN);
        glColor3f(1.0f, 0.0f, 0.0f); glVertex2f(-1.0f, 1.0f);
        glColor3f(0.0f, 1.0f, 0.0f); glVertex2f(0.0f, 1.0f);
        glColor3f(0.0f, 0.0f, 1.0f); glVertex2f(0.0f, 0.0f);
        glColor3f(0.0f, 1.0f, 1.0f); glVertex2f(-1.0f, 0.0f);
    glEnd();
}

GLuint Renderer::get_shader_id() {
    return m_shader->get_id();
}

}
