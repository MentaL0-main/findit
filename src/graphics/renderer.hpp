#pragma once

#include <GL/glew.h>
#include <SDL3/SDL.h>

namespace findit {

class Renderer {
public:
    Renderer(SDL_GLContext &gl_context);
    void set_clear_color(float r, float g, float b, float a);
    void clear();
    void present(SDL_Window* window);
    
    [[deprecated("Don't use test function on the release.")]]
    void rectangle();

private:

};

}