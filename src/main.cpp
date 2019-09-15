#include <iostream>
#include <vector>
#include "GameController.h"
#include "GameEngine.h"
#include "GameItem.h"

int main() {

    // Create an instance of the Game Controller
    GameController * gameController = new GameController();

    // Create an instance of the Game Engine
    GameEngine * gameEngine = new GameEngine(gameController);
    gameEngine->startGame();

    return 0;
}