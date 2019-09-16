#ifndef PLAYERITEM_H
#define PLAYERITEM_H

#include <iostream>
#include "../GameItem.h"

class PlayerItem : public GameItem {
    public:
        PlayerItem(int x, int y, int widthInPixels = 20, int heightInPixels = 20) : 
            GameItem(x, y, widthInPixels, heightInPixels) {
            isPlayerControlled = true;
            allowed_moves = allBaseMoves;
            type = GameItemType::player;
        }
        
        // Handle input
        void handleInput(Base_Moves move) {
            if(std::find(allowed_moves.begin(), allowed_moves.end(), move) != allowed_moves.end()) {
                if (!isAlive) { return; }

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
                    default:
                        break;
                }
            }
        }

        void update() {
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