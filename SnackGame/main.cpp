//
//  main.cpp
//  SnackGame
//
//  Created by Song on R 2/05/20.
//  Copyright © Reiwa 2 Sou. All rights reserved.
//

#include <iostream>
#include "Game.hpp"

int main() {
    Game game;
    bool isSuccess = game.Initialize();

    if (isSuccess) {
        game.RunLoop();
    } else {
        std::cout << "Faild\n";
    }

    game.Shutdown();

    return 0;
}
