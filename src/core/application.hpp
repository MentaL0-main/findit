#pragma once

#include "../logger/logger.hpp"
#include "../graphics/window.hpp"
#include "../graphics/renderer.hpp"
#include "../input/keyboard.hpp"
#include "../input/mouse.hpp"

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
    std::unique_ptr<Keyboard> m_keyboard;
    std::unique_ptr<Mouse> m_mouse;

    bool m_running = true;

    void init();
    void mainloop();
    void cleanup();

    void proccess_input();
    void logic();
    void render();
};

}