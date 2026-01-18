#pragma once

#include "../logger/logger.hpp"
#include "../graphics/window.hpp"
#include "../graphics/renderer.hpp"
#include "../input/keyboard.hpp"
#include "../input/mouse.hpp"
#include "../camera/camera.hpp"
#include "../controller/controller.hpp"
#include "../voxel/chunk.hpp"

#include <memory>

namespace findit {

class Application {
public:
    Application(std::shared_ptr<Logger> &logger);
    void run();

private:
    std::shared_ptr<Logger> m_logger;
    std::unique_ptr<Window> m_window;
    std::unique_ptr<Renderer> m_renderer;
    std::shared_ptr<Keyboard> m_keyboard;
    std::shared_ptr<Mouse> m_mouse;
    std::shared_ptr<ResourceManager> m_resource_manager;
    std::shared_ptr<Camera> m_camera;
    std::unique_ptr<Controller> m_controller;
    std::unique_ptr<Chunk> m_chunk;

    bool m_running = true;

    void init();
    void mainloop();
    void cleanup();

    void proccess_input();
    void logic();
    void render();
};

}
