#pragma once

#include <raylib.h>
#include"BSAI25005-MINI-PROJECT-1-Bird.h"
#include "BSAI25005-MINI-PROJECT-1-Pipe.h"
enum GameState
{
    MENU,
    PLAYING,
    GAMEOVER
};

class Game
{
private:
    GameState state;
    Bird bird;
    static const int MAX_PIPES = 5;
    Pipe* pipes[MAX_PIPES];
    Texture2D background;
    float bgX1, bgX2;
    Texture2D bgNormal;
    Texture2D bgUD;
    bool isUpsideDown;
    float switchTimer;
    int score;
    int level;

public:
    Game();

    void startGame();
    void update();
    void draw();
    void handleInput();
    void reset();
};

