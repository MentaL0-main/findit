#pragma once

#include "object.hpp"
#include "shader.hpp"
#include "../ResourceManager/ResourceManager.hpp"

#include <GL/glew.h>
#include <SDL3/SDL.h>
#include <memory>

namespace findit {

class Renderer {
public:
    Renderer(SDL_GLContext &gl_context);
    void set_clear_color(float r, float g, float b, float a);
    void clear();
    void present(SDL_Window* window);

    void render_object(std::shared_ptr<Object> &obj);
    
    [[deprecated("Don't use test function on the release.")]]
    void rectangle();

private:
    std::unique_ptr<ResourceManager> m_resource_manager;
    std::unique_ptr<Shader> m_shader;
};

}