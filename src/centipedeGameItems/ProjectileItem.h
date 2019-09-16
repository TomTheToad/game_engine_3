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
            y -= moveDistanceInPixels;

            yMin = (y - 5);
            yMax = (y + heightInPixels + 5);
            xMin = (x - 5);
            xMax = (x + widthInPixels + 5);

            if(y <= 0) {
                isAlive = false;
            }

            updateSegments(x, y);
        }

    private:
        Base_Moves direction;
};

#endif