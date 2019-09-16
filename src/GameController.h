#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include <vector>
#include "GameItem.h"
#include "centipedeGameItems/Player.h"
#include "centipedeGameItems/CentipedeItem.h"

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
            PlayerItem * player = new PlayerItem((screenWidth / 2),(screenWidth - 100));

            // alter defaults for player based on game board dimensions
            player->yMax = screenHeight;
            player->xMax = screenWidth;
            player->yMin = screenHeight - (screenHeight / 4);

            // Create centipede
            CentipedeItem * centipede = new CentipedeItem(0, 0);
            centipede->xMax = screenWidth;
            centipede->yMax = screenHeight;
            
            gameItems.push_back(player);
            gameItems.push_back(centipede);

        }

        void updateGameItems() {
            // std::cout << "updateGameItems called" << std::endl;
            for (auto * item : gameItems) {
                // Check location of player item

                // Update item
                item->update();
            }
        }

        // poll all items give player(s) input
        // this allow for multiple players of more then one player controlled item
        void sendInputToGameItems(GameItem::Base_Moves move) {
            for (GameItem * item : gameItems) {
                if(item->isPlayerControlled) {
                    item->handleInput(move);
                }
            }
        }
        
};

#endif