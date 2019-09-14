#ifndef GAME_ITEM_H
#define GAME_ITEM_H

#include <iostream>
#include <vector>
#include <string>

class GameItem {
    public:
        
        // TODO: add back when necessary
        // Inner enum with allowed movements
        enum class Base_Moves {left, right, up, down, shoot};
        std::vector<Base_Moves> allBaseMoves {Base_Moves::down, Base_Moves::up, Base_Moves::right, Base_Moves::left, Base_Moves::shoot};
        std::vector<Base_Moves> allowed_moves = {};

        GameItem(int x, int y, int widthInPixels, int heightInPixels) : x(x), y(y), widthInPixels(widthInPixels), heightInPixels(heightInPixels) { }
        virtual ~GameItem() {}

        // Method or macro method to include in an update cycle
        void virtual Update();

        // Handle input
        // TODO: make move amount dynamic
        void handleInput(Base_Moves move) {
            if(std::find(allowed_moves.begin(), allowed_moves.end(), move) != allowed_moves.end()) {
                std::printf("Command received: %d", move);

                switch(move) {
                    case Base_Moves::left:
                        x -= 1;
                        break;
                    case Base_Moves::right:
                        x += 1;
                        break;
                    case Base_Moves::up:
                        y += 1;
                        break;
                    case Base_Moves::down:
                        y -= 1;
                        break;
                    case Base_Moves::shoot:
                        std::cout << "Pew Pew Pew";
                        break;
                }
            }
        }

        // void virtual HandleCollision();
        bool hasImage() { return (imageFile.length() > 0); }

        int x = 0;
        int y = 0;
        int widthInPixels = 10;
        int heightInPixels = 10;

        bool isPlayerControlled = false;

        std::string imageFile;

};

void GameItem::Update() {
    // std::printf("Game item at x:%d y:%d updated!", this->x, this->y);
}

#endif