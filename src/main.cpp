#include <iostream>
#include <vector>
#include "gameItems/GameItem.h"
#include "engine/GameEngine.h"
#include "renderer/RenderController.h"

int main() {

    // TODO: move all this stuff to a game controller / creater

    // Test: Create some game items
    std::vector<GameItem *> gameItems;
    GameItem * g1 = new GameItem(320, 540, 20, 20);
    g1->allowed_moves = g1->allBaseMoves;
    g1->isPlayerControlled = true;

    GameItem * g2 = new GameItem(320, 440, 20, 20);
    g2->allowed_moves = g2->allBaseMoves;
    g2->isPlayerControlled = false;

    gameItems.push_back(g1);
    gameItems.push_back(g2);

    // Test: Create Render Controller
    RenderController * renderController = new RenderController(640, 640, 32, 32, gameItems);

    // Test: Create a game engine
    GameEngine * engine = new GameEngine(gameItems, renderController);
    engine->startGame();
    return 0;
}