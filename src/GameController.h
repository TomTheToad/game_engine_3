#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include <vector>
#include "GameItem.h"

class GameController {
    public:
        int screenWidth = 640;
        int screenHeight = 640;

        // TODO: may not need this
        int gridWidth = 32;
        int gridHeight = 32;

        // frame rate target @ 60 frames per 1000
        unsigned int targetFrameDuration = (1000 / 60);

        std::vector<GameItem *> gameItems = {};

        GameController() {
            buildGameItems();
        }

        void buildGameItems() {
            // create the player item
            GameItem * player = new GameItem(320, 540, 20, 20);
            player->allowed_moves = player->allBaseMoves;
            player->isPlayerControlled = true;

            GameItem * dummy = new GameItem((screenWidth / 2), (screenWidth - 300), 20, 20);
            
            gameItems.push_back(player);
            gameItems.push_back(dummy);

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

            // TODO: make these static?
            unsigned int xMax = screenWidth - player->widthInPixels;
            unsigned int yMax = screenHeight - player->heightInPixels;
            
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