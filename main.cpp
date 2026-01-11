#include <iostream>
#include <vector>
#include <SDL3/SDL.h>

constexpr int WINDOW_WIDTH = 600;
constexpr int WINDOW_HEIGHT = 900;
constexpr int BOX_SIZE = (WINDOW_WIDTH-100)/10;

bool running = true;
SDL_Event event;

SDL_Color background_color = SDL_Color{25, 25, 35, 255};

enum class scenes {
    menu,
    settings,
    game
};

SDL_FRect canvas_rect = {50, 50, WINDOW_WIDTH-100, WINDOW_WIDTH-100};

struct Figure {
    std::vector<SDL_Point> boxes;
    SDL_Color color;
};

Figure gen_figure() {
    return Figure{{{0, 0}, {0, 1}, {1, 0}, {1, 1}}, SDL_Color{255, 255, 255, 255}};
}

std::vector<Figure> figures;

void give_figures() {
    figures.clear();

    for (int i = 0; i < 3; ++i) {
        figures.push_back(gen_figure());
    }
}

void render_scene(SDL_Renderer* renderer, scenes scene) {
    if (scene == scenes::game) [[likely]] {
        SDL_SetRenderDrawColor(renderer, background_color.r,
                                         background_color.g,
                                         background_color.b,
                                         background_color.a);
        SDL_RenderClear(renderer);

        // Canvas
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderFillRect(renderer, &canvas_rect);

        // Canvas lines
        for (int i = 0; i < 10; ++i) {
            SDL_SetRenderDrawColor(renderer, 35, 35, 85, 255);
            SDL_RenderLine(renderer, canvas_rect.x*(i+1), canvas_rect.y, canvas_rect.x*(i+1), canvas_rect.y+canvas_rect.h);
            SDL_RenderLine(renderer, canvas_rect.y, canvas_rect.x*(i+1), canvas_rect.y+canvas_rect.h, canvas_rect.x*(i+1));
        }

        // Canvas ramka
        SDL_SetRenderDrawColor(renderer, 0, 255, 255, 255);
        SDL_RenderRect(renderer, &canvas_rect);

        // Hot bar 

        SDL_RenderPresent(renderer);
    }
}

int main() {
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        std::cerr << "[!] Failed to init sdl3\n";
        return 1;
    }
    
    SDL_Window* window = SDL_CreateWindow("Puzzles", WINDOW_WIDTH, WINDOW_HEIGHT, 0);
    if (!window) {
        std::cerr << "[!] Failed to init window\n";
        SDL_Quit();
        return 2;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, 0);
    if (!renderer) {
        std::cerr << "[!] Failed to init renderer\n";
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 3;
    }

    scenes current_scene = scenes::game;

    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) {
                running = false;
            }
        }

        render_scene(renderer, current_scene);
    }   

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
