#ifndef RENDERCONTROLLER_H
#define RENDERCONTROLLER_H

#include <vector>
#include "SDL.h"
#include "GameItem.h"
#include "GameController.h"

class RenderController {
    public:
        // Fields
        GameController * gameController;

        RenderController(
            GameController * gameController) : gameController(gameController) {
        
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
                gameController->screenWidth,
                gameController->screenHeight, 
                SDL_WINDOW_SHOWN);

            if (nullptr == sdl_window) {
                std::cerr << "Window could not be created.\n";
                std::cerr << " SDL_Error: " << SDL_GetError() << "\n";
            }

            // Create renderer
            sdl_renderer = SDL_CreateRenderer(sdl_window, -1, SDL_RENDERER_ACCELERATED);
            if (nullptr == sdl_renderer) {
                std::cerr << "Renderer could not be created.\n";
                std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
            }

        }

    void render() {
        // Intiate block, extrapolate dimensions
        SDL_Rect block;
        block.w = gameController->screenWidth / gameController->gridWidth;
        block.h = gameController->gridHeight / gameController->gridWidth;

        // Clear the screen
        SDL_SetRenderDrawColor(sdl_renderer, 0x1E, 0x1E, 0x1E, 0xFF);
        SDL_RenderClear(sdl_renderer);

        // TODO: render given game items
        for (auto * item : gameController->gameItems) {
            RenderItem(item, &block);
        }

        // Update Screen
        SDL_RenderPresent(sdl_renderer);
    }

    void RenderItem(GameItem * item, SDL_Rect * block) {
        SDL_SetRenderDrawColor(sdl_renderer, item->red, item->green, item->blue, item->alpha);
        block->w = item->widthInPixels;
        block->h = item->heightInPixels;
        block->x = item->x;
        block->y = item->y;
        SDL_RenderFillRect(sdl_renderer, block);

        if(item->segments.size() > 0) {
            for(auto * segment : item->segments) {
                RenderItem(segment, block);
            }
        }
    }

    ~RenderController() {
        SDL_DestroyWindow(sdl_window);
        SDL_Quit();
    }

    void updateWindowTitle(int score, int fps) {
        std::string title{"Centipede Score: " + std::to_string(score) + " FPS: " + std::to_string(fps)};
        SDL_SetWindowTitle(sdl_window, title.c_str());
    }   

    private:
        SDL_Window * sdl_window;
        SDL_Renderer * sdl_renderer;

};

#endif