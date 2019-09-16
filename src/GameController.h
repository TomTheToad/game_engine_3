#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include <vector>
#include <mutex>
#include "GameItem.h"
#include "centipedeGameItems/ProjectileItem.h"
#include "centipedeGameItems/PlayerItem.h"
#include "centipedeGameItems/CentipedeItem.h"

class GameController {
    public:
        bool isRunning = true;

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
                // Update item
                item->update();

                // check collisions
                if(checkCollisions(item)) {
                    item->isAlive = false;
                }

                // Delete if dead
                if(item->isAlive == false) {
                    deleteGameItem(item);
                }
            }
        }

        // poll all items give player(s) input
        // this allow for multiple players of more then one player controlled item
        void sendInputToGameItems(GameItem::Base_Moves move) {
            for (GameItem * item : gameItems) {
                if(item->isPlayerControlled) {
                    item->handleInput(move);
                    if(move == GameItem::Base_Moves::shoot) {
                        shootProjectile((item->x + (item->widthInPixels / 2)), item->y);
                    }
                }
            }
        }

         // Shoot projectile
        void shootProjectile(int startingX, int startingY) {
            ProjectileItem * bullet = new ProjectileItem(startingX, startingY);
            gameItems.push_back(bullet);
        }

        // TODO: pick one method
        // TODO: break up this method
        bool checkCollisions(GameItem * item) {
            switch(item->type) {
                case GameItem::GameItemType::projectile:
                    for(auto * enemy : gameItems) {
                        if(enemy->type == GameItem::GameItemType::centipede) {
                            if((enemy->x > item->xMin) && (enemy->x < item->xMax) && (enemy->y < item->yMax) && (enemy->y > item->yMin)) {
                                enemy->segments.pop_back();
                                if(enemy->segments.size() <= 0) {
                                    deleteGameItem(enemy);
                                    return true;
                                }
                            }
                        }
                    }
                case GameItem::GameItemType::player:
                    for (auto * enemy : gameItems) {
                        if(enemy->type == GameItem::GameItemType::centipede) {
                            for (auto * segment : enemy->segments) {
                                int delta = 10;
                                int x1 = item->x;
                                int y1 = item->y;
                                int x2 = enemy->x;
                                int y2 = enemy->y;
                                if ((x1 > (x2 - delta)) && (x1 > (x2 + delta)) && (y1 > (y2 - delta)) && (y1 < (y2 + delta))) {
                                    return true;
                                }
                            }
                        }
                    }
                default:
                    return false;
            }
        }

        void deleteGameItem(GameItem * item) {
            std::lock_guard<std::mutex> lock(_mutex);
            gameItems.erase(std::remove(gameItems.begin(), gameItems.end(), item), gameItems.end());
            if(item->type == GameItem::GameItemType::player) {
                isRunning = false;
            }
            delete item;
        }

        private:
            std::mutex _mutex;
};

#endif