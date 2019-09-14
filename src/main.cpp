#include <iostream>
#include <vector>
#include "gameItems/GameItem.h"
#include "engine/GameEngine.h"
#include "renderer/renderController.h"

int main() {

    // TODO: move all this stuff to a game controller / creater

    // Test: Create some game items
    std::vector<GameItem *> gameItems;
    GameItem * g1 = new GameItem(1, 1, 20, 20);
    g1->allowed_moves = g1->allBaseMoves;
    g1->isPlayerControlled = true;
    gameItems.push_back(g1);

    // Test: Create Render Controller
    RenderController * renderController = new RenderController(640, 640, 32, 32);

    // Test: Create a game engine
    GameEngine * engine = new GameEngine(gameItems, renderController);
    engine->startGame();
    return 0;
}