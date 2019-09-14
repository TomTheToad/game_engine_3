#ifndef CENTIPEDE_H
#define CENTIPEDE_H

#include <iostream>
#include <vector>
#include "../gameItems/GameItem.h"
#include "../engine/GameEngine.h"
#include "../renderer/RenderController.h"

class Centipede {
    public:
        // TODO: remove test constructor
        Centipede() {
            // Test: Create some game items
            GameItem * g1 = new GameItem(1, 1, 20, 20);
            g1->allowed_moves = g1->allBaseMoves;
            g1->isPlayerControlled = true;
            gameItems.push_back(g1);

            renderController(640, 640, 32, 32);
            engine(gameItems, renderController);
        }

        void run() {
            engine.startGame();
        }

    private:
        // TODO: fix this
        // RenderController * renderController = new RenderController(640, 640, 32, 32);
        // std::vector<GameItem *> gameItems;
        // GameEngine * engine = new GameEngine(gameItems, renderController); 

        RenderController renderController;
        GameEngine engine;
        std::vector<GameItem *> gameItems;
};

#endif