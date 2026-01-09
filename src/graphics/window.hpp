#pragma once

#include <SDL3/SDL.h>
#include <string>
#include <utility>

namespace findit {

class Window {
public:
    Window(int width, int hegiht, const std::string &title);
    ~Window();

    SDL_Event event;
    SDL_GLContext context;

    void set_size(std::pair<int, int> size);
    void set_title(const std::string &title);

    [[nodiscard]] std::pair<int, int> get_size();
    [[nodiscard]] std::string get_title();
    [[nodiscard]] SDL_Window* get_native_window();

private:
    int m_width, m_height;
    std::string m_title;

    SDL_Window* m_native_window;

};
    
}