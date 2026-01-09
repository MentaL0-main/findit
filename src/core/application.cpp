#include "application.hpp"
#include "../logger/logger.hpp"
#include "../graphics/window.hpp"
#include "../graphics/renderer.hpp"
#include "../input/keyboard.hpp"

#include <glm/ext/vector_float3.hpp>
#include <memory>
#include <SDL3/SDL.h>

namespace findit {

Application::Application(std::shared_ptr<Logger> &logger) {
    m_logger = logger;
}

void Application::run() {
    init();
    mainloop();
    cleanup();
}

void Application::init() {
    m_window = std::make_unique<Window>(1200, 900, "FindIt: Beta");
    m_renderer = std::make_unique<Renderer>(m_window->context);
    m_keyboard = std::make_unique<Keyboard>();
    m_mouse = std::make_unique<Mouse>();
    m_obj = std::make_shared<Object>(std::vector<float> {
                                        -0.5f, -0.5f, 0.0f,
                                        0.5f, -0.5f, 0.0f,
                                        0.0f, 0.5f, 0.0f,
                                     });

    m_renderer->set_clear_color(0.2f, 0.2f, 0.3f, 1.0f);
}

void Application::mainloop() {
    while (m_running) {
        while (SDL_PollEvent(&m_window->event)) {
            if (m_window->event.type == SDL_EVENT_QUIT) {
                m_running = false;
            }

            m_mouse->update_data(m_window->event);
        }

        proccess_input();
        logic();
        render();

    }
}

void Application::cleanup() {}

void Application::proccess_input() {
    if (m_keyboard->is_key_down(SDL_SCANCODE_ESCAPE)) {
        m_running = false;
    }
}

void Application::logic() {

}

void Application::render() {
    m_renderer->clear();

    m_renderer->render_object(m_obj);

    m_renderer->present(m_window->get_native_window());
}

}