#ifndef RENDERCONTROLLER_H
#define RENDERCONTROLLER_H

#include <vector>
#include "SDL.h"
#include "GameItem.h"

class RenderController {
    public:
        // Fields
        std::vector<GameItem *> gameItems; 

        // Constructor TODO: move to cpp? do we need grid?
        RenderController(
            unsigned int window_width,
            unsigned int window_height,
            unsigned int grid_width,
            unsigned int grid_height,
            std::vector<GameItem *> gameItems)
            : 
            window_width(window_width), 
            window_height(window_height), 
            grid_width(grid_width),
            grid_height(grid_height),
            gameItems(gameItems)
            {
        
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
        for (auto * item : gameItems) {
            RenderItem(item, &block);
        }

        // Update Screen
        SDL_RenderPresent(sdl_renderer);
    }

    void RenderItem(GameItem * item, SDL_Rect * block) {
        SDL_SetRenderDrawColor(sdl_renderer, item->red, item->green, item->blue, item->alpha);
        block->x = item->x;
        block->y = item->y;
        SDL_RenderFillRect(sdl_renderer, block);
    }

    ~RenderController() {
        SDL_DestroyWindow(sdl_window);
        SDL_Quit();
    }

    unsigned int getWindowWidth() { return window_width; }
    unsigned int getWindowHeight() { return window_height; }
    unsigned int getGridWidth() { return grid_width; }
    unsigned int getGridHeight() { return grid_height; }

    private:
        unsigned int window_width;
        unsigned int window_height;
        unsigned int grid_width;
        unsigned int grid_height;

        SDL_Window * sdl_window;
        SDL_Renderer * sdl_renderer;

};

#endif