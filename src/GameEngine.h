#ifndef GAMEENGINE_H
#define GAMEENGINE_H

// Test includes
#include <iostream>

// Required includes
#include <vector>
#include "GameItem.h"
#include "SDL.h"
#include "RenderController.h"
#include "GameController.h"

class GameEngine {

    public:
        // Public methods
        GameEngine(GameController * gameController) : gameController(gameController) {
            renderController = new RenderController(gameController);
        }

        ~GameEngine() {
            // nothing to do here either
        }

        void startGame() { 
            gameController->isRunning = true;
            run();
        }

        void stopGame() {
            gameController->isRunning = false;
        }

    private:
        // Private fields
        GameController * gameController;
        RenderController * renderController;

        // Private sdl event
        SDL_Event e;

        // Frame Duration Fields
        unsigned int frameStart;
        unsigned int frameEnd;
        unsigned int frameDuration;
        unsigned int frameCount;

        // Private methods
        // Main game engine loop macro
        void run() {
            unsigned int titleTimeStamp = SDL_GetTicks();
            frameCount = 0;

            std::cout << "Game is running" << std::endl;
            while(gameController->isRunning) {

                // Get frame start time
                frameStart = SDL_GetTicks();

                // 1) Check for input
                checkForInput();
                // 2) Update game items
                update();
                // 3) Render to the screen
                render();
                frameEnd = SDL_GetTicks();

                // Keep track of how long each loop takes
                frameCount++;
                frameDuration = frameEnd - frameStart;

                // After every second, update the window title.
                if (frameEnd - titleTimeStamp >= 1000) {
                    renderController->updateWindowTitle(gameController->score, gameController->level, frameCount);
                    frameCount = 0;
                    titleTimeStamp = frameEnd;
                }

                // If cycling too fast, delay render
                if(frameDuration < gameController->targetFrameDuration) {
                    SDL_Delay(gameController->targetFrameDuration - frameDuration);
                }

            }
            std::cout << "Game has stopped" << std::endl;
        }

        void update() {
            gameController->updateGameItems();

        }

        void render() {
            renderController->render();
        }

        // TODO: move to input or game controller?
        void checkForInput() {
            while(SDL_PollEvent(&e)) {
                if(e.type == SDL_QUIT) {
                    gameController->isRunning = false;
                } else if (e.type == SDL_KEYDOWN) {
                    switch(e.key.keysym.sym) {
                        case SDLK_UP:
                            gameController->sendInputToGameItems(GameItem::Base_Moves::up);
                            break;
                        case SDLK_DOWN:
                            gameController->sendInputToGameItems(GameItem::Base_Moves::down);
                            break;
                        case SDLK_LEFT:
                            gameController->sendInputToGameItems(GameItem::Base_Moves::left);
                            break;
                        case SDLK_RIGHT:
                            gameController->sendInputToGameItems(GameItem::Base_Moves::right);
                            break;
                        case SDLK_SPACE:
                            gameController->sendInputToGameItems(GameItem::Base_Moves::shoot);
                            break;
                    }
                }
            }
        }
};

#endif