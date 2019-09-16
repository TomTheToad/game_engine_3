#ifndef PROJECTILEITEM_H
#define PROJECTILEITEM_H

#include "../GameItem.h"

class ProjectileItem : public GameItem {
    public: 

        ProjectileItem(int x, int y, int widthInPixels = 3, int heightInPixels = 6) :
            GameItem(x, y, widthInPixels, heightInPixels, 5) {
                allowed_moves = {Base_Moves::up};
                direction = Base_Moves::up;
                moveDistanceInPixels = 10;
                type = GameItemType::projectile;
        }

        void update() {

            // Continuously move up
            y -= moveDistanceInPixels;

            // If y is less then 0, off the board, remove
            if(y <= 0) {
                isAlive = false;
            }

            // Update the following segments
            updateSegments(x, y);
        }

    private:
        Base_Moves direction;
};

#endif