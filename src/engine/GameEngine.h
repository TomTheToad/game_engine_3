// Game engine requirements
// 1) SDL2 Renderer
// 2) Game Input Handler/ Controller
// 3) Game Items (game pieces, game board, etc.)

#ifndef GAMEENGINE_H
#define GAMEENGINE_H

// Test includes
#include <iostream>

// Required includes
#include <vector>
#include "../gameItems/GameItem.h"
#include "SDL.h"
#include "../renderer/RenderController.h"

class GameEngine {

    public:
        // Public methods
        bool getIsRunning() { return isRunning; }

        void startGame() { 
            isRunning = true;
            run();
        }

        void stopGame() {
            isRunning = false;
        }

        GameEngine(std::vector<GameItem *> gameItems, RenderController * renderController) :
            gameItems(gameItems), renderController(renderController) { }

        ~GameEngine() {
            // nothing to do here either
        }

    private:
        // Private fields
        bool isRunning = false;
        std::vector<GameItem *> gameItems;
        RenderController * renderController;
        SDL_Event e;

        // Private methods

        // Main game engine loop macro
        void run() {
            std::cout << "Game is running" << std::endl;
            while(isRunning) {

                // TODO: 3 things
                // 1) Check for input
                checkForInput();
                // 2) Update game items
                updateGameItems();
                // 3) Render to the screen
                renderController->render();

            }
            std::cout << "Game has stopped" << std::endl;
        }

        void updateGameItems() {
            for (GameItem * item : gameItems) {
                // Check location of player item

                if (item->isPlayerControlled) {
                    checkLocationOfPlayer(item);
                }

                // Update item
                item->Update();
            }
        }

        // TODO: Make this a generic check so can use with NPCs as well.
        void checkLocationOfPlayer(GameItem * player) {
            unsigned int xMax = renderController->getWindowWidth() - player->widthInPixels;
            unsigned int yMax = renderController->getWindowHeight() - player->heightInPixels;
            
            if (player->x < 0) {
                player->x = 0;
            } else if (player->x > xMax) {
                player->x = xMax; 
            } else if (player->y < 0) {
                player->y = 0;
            } else if (player->y > yMax) {
                player->y = yMax;
            }
        }

        void checkForInput() {
            while(SDL_PollEvent(&e)) {
                if(e.type == SDL_QUIT) {
                    isRunning = false;
                } else if (e.type == SDL_KEYDOWN) {
                    switch(e.key.keysym.sym) {
                        case SDLK_UP:
                            sendInputToGameItems(GameItem::Base_Moves::up);
                            std::cout << "Up" << std::endl;
                            break;
                        case SDLK_DOWN:
                            sendInputToGameItems(GameItem::Base_Moves::down);
                            std::cout << "Down" << std::endl;
                            break;
                        case SDLK_LEFT:
                            sendInputToGameItems(GameItem::Base_Moves::left);
                            std::cout << "Left" << std::endl;
                            break;
                        case SDLK_RIGHT:
                            sendInputToGameItems(GameItem::Base_Moves::right);
                            std::cout << "Right" << std::endl;
                            break;
                        case SDLK_SPACE:
                            sendInputToGameItems(GameItem::Base_Moves::shoot);
                            std::cout << "Shoot!" << std::endl;
                            break;
                    }
                }
            }
        }

        // send command to single item
        // void commandGameItem(GameItem::Base_Moves move) {
            
        // }

        // poll all items give player(s) input
        void sendInputToGameItems(GameItem::Base_Moves move) {
            for (GameItem * item : gameItems) {
                if(item->isPlayerControlled) {
                    item->handleInput(move);
                }
            }
        }
};

#endif