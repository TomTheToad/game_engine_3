#ifndef GAMEITEM_H
#define GAMEITEM_H

#include <iostream>
#include <vector>
#include <string>
#include <limits>

class GameItem {
    public:
        // Inner enum for game item types (use for collions detection)
        enum class GameItemType {player, centipede, projectile, general};

        // Inner enum with allowed movements
        enum class Base_Moves {left, right, up, down, shoot};
        std::vector<Base_Moves> allBaseMoves {Base_Moves::down, Base_Moves::up, Base_Moves::right, Base_Moves::left, Base_Moves::shoot};
        std::vector<Base_Moves> allowed_moves = {};

        GameItem(int x, int y, int widthInPixels, int heightInPixels, int numStartingSegments=0) :
            x(x), y(y), widthInPixels(widthInPixels), heightInPixels(heightInPixels), numStartingSegments(numStartingSegments) {
                // Initialize segments, default direction first allowed.
                buildSegments(numStartingSegments);
            }
        virtual ~GameItem() {}

        // Method or macro method to include in an update cycle
        void virtual update() {}

        // Recursively build segments if present
        void virtual buildSegments(int numSegments) {
            for(int i = 0; i < numSegments; i++) {
                GameItem * segment = new GameItem(x, y, widthInPixels, heightInPixels);
                segments.push_back(segment);
            }
        }

        // Update segments
        void virtual updateSegments(int headX, int headY) {
            int prevX = headX;
            int prevY = headY;
            for (auto * segment : segments) {
                // save former x and y
                segment->lastX = segment->x;
                segment->lastY = segment->y;

                // set new x and y
                segment->x = prevX;
                segment->y = prevY;

                prevX = segment->lastX;
                prevY = segment->lastY;
            }
        }

        // Handle input
        void virtual handleInput(Base_Moves move) {
            return;
        }

        bool hasImage() { return (imageFile.length() > 0); }
        GameItemType type = GameItemType::general;

        // location
        int x = 0;
        int y = 0;
        int widthInPixels;
        int heightInPixels;
        int moveDistanceInPixels = 10;
        int lastY = 0;
        int lastX = 0;

        // Item game specific details with defaults
        bool isPlayerControlled = false;
        bool isAlive = true;
        std::vector<GameItem *> enemies = {};

        // for chain items
        int numStartingSegments = 0;
        std::vector<GameItem *> segments;

        // virtual container bounds
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