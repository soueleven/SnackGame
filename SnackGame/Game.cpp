//
//  Game.cpp
//  SnackGame
//
//  Created by Song on R 2/05/20.
//  Copyright © Reiwa 2 Sou. All rights reserved.
//

#include <time.h>
#include "Game.hpp"

const int HEIGHT = 480;
const int WIDTH = 640;

const int DIRECTION_UP = 0;
const int DIRECTION_DOWN = 1;
const int DIRECTION_RIGHT = 2;
const int DIRECTION_LEFT = 3;

Game::Game()
:window(nullptr)
,renderer(nullptr)
,isRunning(true)
,ticksCount(0)
{}

void RandomFeedPosition(Snack snack, vector2 *feed) {
    feed->x = (rand() % (WIDTH - POINT_WH) / 10 + 1) * 10;
    feed->y = (rand() % (HEIGHT - POINT_WH) / 10 + 1) * 10;
    while (snack.SearchNode(*feed) > -1) {
        feed->x = (rand() % (WIDTH - POINT_WH) / 10 + 1) * 10;
        feed->y = (rand() % (HEIGHT - POINT_WH) / 10 + 1) * 10;
    }
}

bool Game::Initialize() {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
        return false;
    }

    window = SDL_CreateWindow(
        "",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        WIDTH,
        HEIGHT,
        SDL_WINDOW_OPENGL
    );

    if (window == NULL) {
        SDL_Log("Failed to create windows: %s", SDL_GetError());
        return false;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED|SDL_RENDERER_PRESENTVSYNC);
    if (renderer == NULL) {
        SDL_Log("Failed to create renderer: %s", SDL_GetError());
        return false;
    }

    direction = DIRECTION_RIGHT;

    snack = Snack();
    snack.InsertHead(vector2{WIDTH/2-POINT_WH*4, HEIGHT/2});
    snack.InsertHead(vector2{WIDTH/2-POINT_WH*3, HEIGHT/2});
    snack.InsertHead(vector2{WIDTH/2-POINT_WH*2, HEIGHT/2});
    snack.InsertHead(vector2{WIDTH/2-POINT_WH*1, HEIGHT/2});

    srand((unsigned int)time(NULL));
    RandomFeedPosition(snack, &feed);

    return true;
}

void Game::RunLoop() {
    while (isRunning) {
        ProcessInput();
        UpdateGame();
        GenerateOutput();
    }
}

void Game::ProcessInput() {
    SDL_Event event;
    while(SDL_PollEvent(&event)) {
        switch(event.type) {
            case SDL_QUIT:
                isRunning = false;
                break;
            default:
                break;
        }
    }

    const Uint8* state = SDL_GetKeyboardState(NULL);

    if (state[SDL_SCANCODE_ESCAPE]) {
        isRunning = false;
    }

    if (state[SDL_SCANCODE_UP] && (direction != DIRECTION_DOWN)) {
        direction = DIRECTION_UP;
    }

    if (state[SDL_SCANCODE_DOWN] && (direction != DIRECTION_UP)) {
        direction = DIRECTION_DOWN;
    }

    if (state[SDL_SCANCODE_RIGHT] && (direction != DIRECTION_LEFT)) {
        direction = DIRECTION_RIGHT;
    }

    if (state[SDL_SCANCODE_LEFT] && (direction != DIRECTION_RIGHT)) {
        direction = DIRECTION_LEFT;
    }
}

void Game::UpdateGame() {
}

void Game::GenerateOutput() {
    // Generate Background
    SDL_SetRenderDrawColor(renderer, 0, 128, 0, 255);
    SDL_RenderClear(renderer);

    // Generate Snack
    SDL_SetRenderDrawColor(renderer, 192, 192, 192, 192);
    SnackNode *current = snack.GetFirst();
    while (current != 0) {
        SDL_Rect node{
            static_cast<int>(current->GetPos().x),
            static_cast<int>(current->GetPos().y),
            POINT_WH, // Width
            POINT_WH // Height
        };
        SDL_RenderFillRect(renderer, &node);
        current = current->GetNext();
    }

    SDL_SetRenderDrawColor(renderer, 255, 50, 0, 255);
    // Generate Feed
    SDL_Rect appleNode{
        static_cast<int>(feed.x),
        static_cast<int>(feed.y),
        POINT_WH, // Width
        POINT_WH // Height
    };
    SDL_RenderFillRect(renderer, &appleNode);

    SDL_RenderPresent(renderer);
}

void Game::Shutdown() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
