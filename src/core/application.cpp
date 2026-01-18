#include "application.hpp"
#include "../logger/logger.hpp"
#include "../graphics/window.hpp"
#include "../graphics/renderer.hpp"
#include "../input/keyboard.hpp"

#include <ctime>
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
    srand(time(NULL));

    std::vector<Voxel> voxels;
    for (int i = 0; i < 10; ++i)
        for (int j = 0; j < 10; ++j)
            voxels.push_back({{i, j, 0}, {1, 1, 0}, true});

    m_window = std::make_unique<Window>(1200, 900, "FindIt: Beta", m_logger);
    m_renderer = std::make_unique<Renderer>(m_window->context, m_logger);
    m_keyboard = std::make_shared<Keyboard>();
    m_mouse = std::make_shared<Mouse>();
    m_resource_manager = std::make_unique<ResourceManager>(m_logger);
    m_camera = std::make_shared<Camera>(m_window->get_size().first, m_window->get_size().second, m_logger);
    m_controller = std::make_unique<Controller>();
    m_chunk = std::make_unique<Chunk>(voxels);

    m_renderer->set_clear_color(0.7f, 0.7f, 1.0f, 1.0f);
    m_window->set_cursor_visible(true);

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
    m_controller->proccess(m_camera, m_keyboard, m_mouse);

    m_camera->push(m_renderer->get_shader_id());
    m_camera->update();

    m_mouse->reset_relative();
}

void Application::render() {
    m_renderer->clear();

    m_chunk->render(m_renderer->get_shader_id());

    m_renderer->present(m_window->get_native_window());
}

}
