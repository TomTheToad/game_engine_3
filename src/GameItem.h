#ifndef GAMEITEM_H
#define GAMEITEM_H

#include <iostream>
#include <vector>
#include <string>
#include <limits>

class GameItem {
    public:
        
        // Inner enum with allowed movements
        enum class Base_Moves {left, right, up, down, shoot};
        std::vector<Base_Moves> allBaseMoves {Base_Moves::down, Base_Moves::up, Base_Moves::right, Base_Moves::left, Base_Moves::shoot};
        std::vector<Base_Moves> allowed_moves = {};

        GameItem(int x, int y, int widthInPixels, int heightInPixels) :
            x(x), y(y), widthInPixels(widthInPixels), heightInPixels(heightInPixels) { }
        virtual ~GameItem() {}

        // Method or macro method to include in an update cycle
        void virtual update() {}

        // Handle input
        void virtual handleInput(Base_Moves move) {
            return;
        }

        // void virtual HandleCollision();
        bool hasImage() { return (imageFile.length() > 0); }

        // location
        int x = 0;
        int y = 0;
        int widthInPixels = 10;
        int heightInPixels = 10;

        // Item game specific details with defaults
        bool isPlayerControlled = false;
        int moveDistanceInPixels = 10;
        int xMin = 0;
        int xMax = std::numeric_limits<int>::max();
        int yMin = 0;
        int yMax = std::numeric_limits<int>::max();

        // red green blue alpha : default = gray
        unsigned char red = 111;
        unsigned char green = 115;
        unsigned char blue = 115;
        unsigned char alpha = 1;
        
        // Texture map
        std::string imageFile;

};

#endif