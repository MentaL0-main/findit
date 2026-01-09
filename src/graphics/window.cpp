#include "window.hpp"

#include <SDL3/SDL.h>
#include <SDL3/SDL_video.h>
#include <stdexcept>

namespace findit {

Window::Window(int width, int height, const std::string &title) {
    m_width = width;
    m_height = height;
    m_title = title;

    if (!SDL_Init(SDL_INIT_VIDEO)) {
        throw std::runtime_error("[!] Failed to init sdl3: " + std::string(SDL_GetError()));
    }

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    m_native_window = SDL_CreateWindow(m_title.c_str(), m_width, m_height, SDL_WINDOW_OPENGL);
    if (!m_native_window) {
        throw std::runtime_error("[!] Failed to init window: " + std::string(SDL_GetError()));
    }

    context = SDL_GL_CreateContext(m_native_window);
    if (!context) {
        throw std::runtime_error("[!] Failed to init context: " + std::string(SDL_GetError()));
    }

    SDL_GL_MakeCurrent(m_native_window, context);
    if (context != SDL_GL_GetCurrentContext()) {
        throw std::runtime_error("[!] Failed to make context to current: " + std::string(SDL_GetError()));
    }
}

Window::~Window() {
    SDL_GL_DestroyContext(context);
    SDL_DestroyWindow(m_native_window);
    SDL_Quit();
}

void Window::set_size(std::pair<int, int> size) {
    m_width = size.first;
    m_height = size.second;
}

void Window::set_title(const std::string &title) {
    m_title = title;
}

std::pair<int, int> Window::get_size() {
    return std::pair<int, int>{m_width, m_height};
}

std::string Window::get_title() {
    return m_title;
}

SDL_Window* Window::get_native_window() {
    return m_native_window;
}

}