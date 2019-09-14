#ifndef RENDERCONTROLLER_H
#define RENDERCONTROLLER_H

#include "SDL.h"

class RenderController {
    public:
        // Constructor TODO: move to cpp? do we need grid?
        RenderController(unsigned int window_width, unsigned int window_height, unsigned int grid_width, unsigned int grid_height)
        : window_width(window_width), window_height(window_height), grid_width(grid_width), grid_height(grid_height) {
        
            // Initialize SDL
            if (SDL_Init(SDL_INIT_VIDEO) < 0) {
                std::cerr << "SDL could not initialize.\n";
                std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
            }

            // Create Window
            sdl_window = SDL_CreateWindow(
                "BGE",
                SDL_WINDOWPOS_CENTERED,
                SDL_WINDOWPOS_CENTERED, 
                window_width,
                window_height, 
                SDL_WINDOW_SHOWN);

            if (nullptr == sdl_window) {
                std::cerr << "Window could not be created.\n";
                std::cerr << " SDL_Error: " << SDL_GetError() << "\n";
            }

            // Create renderer
            // sdl_renderer = SDL_CreateRenderer(sdl_window, -1, SDL_RENDERER_ACCELERATED | SDL_WINDOW_MAXIMIZED);
            sdl_renderer = SDL_CreateRenderer(sdl_window, -1, SDL_RENDERER_ACCELERATED);
            if (nullptr == sdl_renderer) {
                std::cerr << "Renderer could not be created.\n";
                std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
            }

        }

    void render() {
        // Intiate block, extrapolate dimensions

        // TODO: Is this all necessary?
        SDL_Rect block;
        block.w = window_width / grid_width;
        block.h = window_height / grid_height;

        // Clear the screen
        SDL_SetRenderDrawColor(sdl_renderer, 0x1E, 0x1E, 0x1E, 0xFF);
        SDL_RenderClear(sdl_renderer);

        // TODO: render given game items

        // Update Screen
        SDL_RenderPresent(sdl_renderer);
    }

    ~RenderController() {
        SDL_DestroyWindow(sdl_window);
        SDL_Quit();
    }

    private:
        unsigned int window_width;
        unsigned int window_height;
        unsigned int grid_width;
        unsigned int grid_height;

        SDL_Window * sdl_window;
        SDL_Renderer * sdl_renderer;

};

#endif