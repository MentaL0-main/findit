#include "renderer.hpp"
#include "object.hpp"
#include "shader.hpp"

#include <SDL3/SDL.h>
#include <iostream>
#include <memory>
#include <stdexcept>

namespace findit {

Renderer::Renderer(SDL_GLContext &gl_contex) {
    glewExperimental = GL_TRUE;
    GLenum err = glewInit();
    if (err != GLEW_OK) {
        std::cerr << "ERROR: " << glewGetErrorString(err) << std::endl;
        throw std::runtime_error("[!] Failed to init glew");
    }

    m_resource_manager = std::make_unique<ResourceManager>();

    m_shader = std::make_unique<Shader>(m_resource_manager->loadShader("../assets/shaders/vertex.glsl"),
                                        m_resource_manager->loadShader("../assets/shaders/fragment.glsl"));

    glEnable(GL_DEPTH_TEST);
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

void Renderer::render_object(std::shared_ptr<Object> &obj) {
    glUseProgram(m_shader->get_id());
    glBindVertexArray(obj->get_vao());
    glDrawArrays(GL_TRIANGLES, 0, obj->get_vertices_count()/3);
}

void Renderer::rectangle() {
    glBegin(GL_TRIANGLE_FAN);
        glColor3f(1.0f, 0.0f, 0.0f); glVertex2f(-1.0f, 1.0f);
        glColor3f(0.0f, 1.0f, 0.0f); glVertex2f(0.0f, 1.0f);
        glColor3f(0.0f, 0.0f, 1.0f); glVertex2f(0.0f, 0.0f);
        glColor3f(0.0f, 1.0f, 1.0f); glVertex2f(-1.0f, 0.0f);
    glEnd();
}

}