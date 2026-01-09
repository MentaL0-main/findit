#include "renderer.hpp"

#include <SDL3/SDL.h>
#include <SDL3/SDL_video.h>
#include <iostream>
#include <stdexcept>

namespace findit {

Renderer::Renderer(SDL_GLContext &gl_contex) {
    glewExperimental = GL_TRUE;
    GLenum err = glewInit();
    if (err != GLEW_OK) {
        std::cerr << "ERROR: " << glewGetErrorString(err) << std::endl;
        throw std::runtime_error("[!] Failed to init glew");
    }
}

void Renderer::set_clear_color(float r, float g, float b, float a) {
    glClearColor(r, g, b, a);
}

void Renderer::clear() {
    glClear(GL_COLOR_BUFFER_BIT);
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

}