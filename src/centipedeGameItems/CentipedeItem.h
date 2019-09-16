#ifndef CENTIPEDEITEM_H
#define CENTIPEDEITEM_H

#include "../GameItem.h"

class CentipedeItem : public GameItem {
    public:

        CentipedeItem(int x, int y, int widthInPixels = 10, int heightInPixels = 10) :
            GameItem(x, y, widthInPixels, heightInPixels, 50) {
                allowed_moves = {Base_Moves::down, Base_Moves::left, Base_Moves::right};
                // TODO: make direction dynamic
                direction = Base_Moves::right;
                moveDistanceInPixels = 5;
                type = GameItemType::centipede;
        }

        // TODO: make movement random
        // TODO: needs own thread / speed
        // Override update
        void update() {

            if (x < xMin) {
                x = 0;
                handleInput(Base_Moves::down);
                direction = Base_Moves::right;
            } else if (x > xMax) {
                x = xMax - widthInPixels;
                handleInput(Base_Moves::down);
                direction = Base_Moves::left;
            } else if (y > yMax - heightInPixels) {
                y = 0;
                direction = Base_Moves::right;
            } else {
                handleInput(direction);
            }
        }

       // Override handleInput
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
                    case Base_Moves::down:
                        y += (2 * heightInPixels);
                        break;
                    default:
                        break;
                }
                updateSegments(x, y);
            }
        }

    private:
        Base_Moves direction;

};

#endif