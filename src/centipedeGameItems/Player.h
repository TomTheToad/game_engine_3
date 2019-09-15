#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include "../GameItem.h"

class Player : public GameItem {
    public:
        Player(int x, int y, int widthInPixels, int heightInPixels) : 
        GameItem(x, y, widthInPixels, heightInPixels) {
            isPlayerControlled = true;
            allowed_moves = allBaseMoves;
        }
        
        // Handle input
        void handleInput(Base_Moves move) {
            if(std::find(allowed_moves.begin(), allowed_moves.end(), move) != allowed_moves.end()) {
                // std::printf("Command received: %d", move);

                switch(move) {
                    case Base_Moves::left:
                        x -= moveDistanceInPixels;
                        break;
                    case Base_Moves::right:
                        x += moveDistanceInPixels;
                        break;
                    case Base_Moves::up:
                        y -= moveDistanceInPixels;
                        break;
                    case Base_Moves::down:
                        y += moveDistanceInPixels;
                        break;
                    case Base_Moves::shoot:
                        std::cout << "Pew Pew Pew";
                        break;
                }
            }
        }

        void update() {
            // std::cout << "updated reached" << std::endl;
            if (x < xMin) {
                x = 0;
            } else if (x > xMax - widthInPixels) {
                x = xMax - widthInPixels; 
            } else if (y < yMin) {
                y = yMin;
            } else if (y > yMax - heightInPixels) {
                y = yMax - heightInPixels;
            }
        }


};

#endif