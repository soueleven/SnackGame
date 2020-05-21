//
//  Game.hpp
//  SnackGame
//
//  Created by Song on R 2/05/20.
//  Copyright © Reiwa 2 Sou. All rights reserved.
//

#ifndef Game_hpp
#define Game_hpp

#include <stdio.h>
#include <SDL2/SDL.h>

class Game {
public:
    Game();
    bool Initialize();
    void RunLoop();
    void Shutdown();
private:
    void ProcessInput();
    void UpdateGame();
    void GenerateOutput();

    SDL_Window* window;
    SDL_Renderer* renderer;

    bool isRunning;
    Uint32 ticksCount;
};

#endif /* Game_hpp */
