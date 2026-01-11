#include "window.hpp"

#include <SDL3/SDL.h>
#include <SDL3/SDL_mouse.h>
#include <SDL3/SDL_video.h>
#include <stdexcept>
#include <SDL3_image/SDL_image.h>

namespace findit {

Window::Window(int width, int height, const std::string &title, std::shared_ptr<Logger> &logger) {
    m_width = width;
    m_height = height;
    m_title = title;
    m_logger = logger;

    if (!SDL_Init(SDL_INIT_VIDEO)) {
        throw std::runtime_error("[!] 'WINDOW' Failed to init sdl3: " + std::string(SDL_GetError()));
    }

    m_logger->log("[+] 'WINDOW' Init sdl3", m_logger->GREEN);

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    
    m_logger->log("[+] 'WINDOW' Attribute SDL_GL_CONTEXT_MAJOR_VERSION: 3", m_logger->GRAY);
    m_logger->log("[+] 'WINDOW' Attribute SDL_GL_CONTEXT_MINOR_VERSION: 3", m_logger->GRAY);
    m_logger->log("[+] 'WINDOW' Attribute SDL_GL_CONTEXT_PROFILE_CORE: SDL_GL_CONTEXT_PROFILE_CORE", m_logger->GRAY);

    m_native_window = SDL_CreateWindow(m_title.c_str(), m_width, m_height, SDL_WINDOW_OPENGL);
    if (!m_native_window) {
        throw std::runtime_error("[!] 'WINDOW' Failed to create window: " + std::string(SDL_GetError()));
    }

    m_logger->log("[+] 'WINDOW' Create window", m_logger->GREEN);


    context = SDL_GL_CreateContext(m_native_window);
    if (!context) {
        throw std::runtime_error("[!] 'WINDOW' Failed to create context: " + std::string(SDL_GetError()));
    }

    m_logger->log("[+] 'WINDOW' Create context", m_logger->GREEN);

    SDL_GL_MakeCurrent(m_native_window, context);
    if (context != SDL_GL_GetCurrentContext()) {
        throw std::runtime_error("[!] 'WINDOW' Failed to make context to current: " + std::string(SDL_GetError()));
    }

    m_logger->log("[+] 'WINDOW' Make context to current", m_logger->GREEN);
}

Window::~Window() {    
    set_cursor_visible(false);
    SDL_GL_DestroyContext(context);
    m_logger->log("[+] 'WINDOW' Destroy context", m_logger->GREEN);
    SDL_DestroyWindow(m_native_window);
    m_logger->log("[+] 'WINDOW' Destroy window", m_logger->GREEN);
    SDL_Quit();
    m_logger->log("[+] 'WINDOW' Quit sdl3", m_logger->GREEN);
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

void Window::set_cursor_visible(bool mode) {
    SDL_SetWindowRelativeMouseMode(m_native_window, mode);
}

}