# CppNanoDegree: Capstone project Centipede (formerly game_engine_3)

## Introduction

I chose to build my own game loosely based on the example [Snake game](https://github.com/udacity/CppND-Capstone-Snake-Game) from Udacity. I really liked the mechanic that was used for the snake body in the given game so I decided to dry and develop something similar. I figured that the classic Centipede game concept would be close.

You can easily launch the game from home/workspace/game_engine_3/build/  by typing ./centipede

My working repository can be found [here](https://github.com/TomTheToad/game_engine_3)

## Game Play
The controls:
 The arrows (up, down, left, right) allow you to move your player piece, a cannon, around the bottom third of the screen.
 Press the space bar to shoot.
 
 The goal is too shoot the centipede until no segments are left. If you manage to kill the centipede, another one, moving 25% faster will take it's place. If you get too close ... game over! Enjoy.

## Known issue with Udacity TurboVNC server:
I have had to make this fix a number of times
When running cmake .. && make from the build folder you may get a error related to white space.
Hopefully you'll just be able to run the executable as is.

The solution can be found [here](https://stackoverflow.com/questions/45730098/cmake-leading-or-trailing-whitespace-policy-cmp0004)

A file at this location: /usr/lib/x86_64-linux-gnu/cmake/SDL2/sdl2-config.cmake
has white space within quotes: set(SDL2_LIBRARIES "-L${SDL2_LIBDIR}  -lSDL2 ").
You must remove the white space set(SDL2_LIBRARIES "-L${SDL2_LIBDIR}  -lSDL2").

The environment refreshes / breaks itself when reloaded. I have no control over this.

## Rubric items

## All required
### Readme:
    current file: README.md
    project: Custom game (Centipede) using SDL2

### Compile and Run
    Please see requirements. I have compiled and tested the source code on the given class environments.
    I developed the game on a mac so the renderer had to be change RenderController.h >> line 38 to SOFTWARE in order to work.

## 5 required
### Loops / Functions / IO
    Control structures are used throughout example GameEngine.h >> line 56 which is the main game loop.
    Code is organized into functions / methods throughout the code >> again pls see the GameEngine.h
    The project accepts user input GameEngine.h >> line 99, PlayerItem.h >> line 18

### Object Oriented Programing
    OOP is used throughout ( note almost everything, if not everything, is an instantiated object )
    Class data members are used throughout
    Member initialization lists are used throughout. Centipede.h >> line 9.
    Class encapsulate behavior. Please see GameController.h
    Classes follow appropriate inheritance hierarchy. (PlayerItem, ProjectileItem, CentipedeItem, overrides GameItem)

### Concurrency
    A mutex lock is utilized in GameController.h >> line 144 to prevent segment faults.

## File structure

Root directory is located at home/workspace/game_engine_3/

/ root level /
build ( <-- will need to be created as indicated below)
GameController.h
GameEngine.h
GameItem.h
main.cpp
README.md
RenderController.h
CMakeLists.txt

/ subdirectory /
centipedeGameItems
  - CentipedeItem.h
  - PlayerItem.h
  - ProjectileItem.h

## Dependencies from Udacity Starter project found [here](https://github.com/udacity/CppND-Capstone-Hello-World)
* cmake >= 3.7
  * All OSes: [click here for installation instructions](https://cmake.org/install/)
* make >= 4.1 (Linux, Mac), 3.81 (Windows)
  * Linux: make is installed by default on most Linux distros
  * Mac: [install Xcode command line tools to get make](https://developer.apple.com/xcode/features/)
  * Windows: [Click here for installation instructions](http://gnuwin32.sourceforge.net/packages/make.htm)
* SDL2 >= 2.0
  * All installation instructions can be found [here](https://wiki.libsdl.org/Installation)
  * Note that for Linux, an `apt` or `apt-get` installation is preferred to building from source.
* gcc/g++ >= 5.4
  * Linux: gcc / g++ is installed by default on most Linux distros
  * Mac: same deal as make - [install Xcode command line tools](https://developer.apple.com/xcode/features/)
  * Windows: recommend using [MinGW](http://www.mingw.org/)

  ## Basic Build Instructions

1. Clone this repo.
2. Make a build directory in the top level directory: `mkdir build && cd build`
3. Compile: `cmake .. && make`
4. Run it: `./Centipede`.