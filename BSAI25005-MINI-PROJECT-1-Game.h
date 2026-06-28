#include "BSAI25005-MINI-PROJECT-1-Game.h"
Game::Game()
{
    bgNormal = LoadTexture("ud.png");
    bgUD = LoadTexture("ruu.png");
    background = bgNormal;
    isUpsideDown = false;
    bgX1 = 0;
    bgX2 = background.width;
    state = MENU;
    score = 0;
    level = 1;
    for (int i = 0; i < MAX_PIPES; i++)
        pipes[i] = nullptr;
}
void Game::startGame()
{
    score = 0;
    bird.reset();
    float speed = (level == 1) ? 200 : 350;
    float gap = (level == 1) ? 150 : 120;

    for (int i = 0; i < MAX_PIPES; i++) {
        if (pipes[i] != nullptr)
            delete pipes[i];
        pipes[i] = new Pipe(600 + i * 300, gap, speed);
    }
    state = PLAYING;
}

void Game::reset()
{
    for (int i = 0; i < MAX_PIPES; i++)
        delete pipes[i];

    level = 1;
    state = MENU;
}

void Game::handleInput()
{
    if (state == MENU)
    {
        if (IsKeyPressed(KEY_ENTER))
            startGame();

        if (IsKeyPressed(KEY_Q))
            CloseWindow();
    }

    if (state == PLAYING)
    {
        if (IsKeyPressed(KEY_SPACE))
            bird.flap();

        if (IsKeyPressed(KEY_U))
        {
            level++;
            if (level > 2)
                level = 1;

            startGame();
        }
    }
    if (IsKeyPressed(KEY_G))
    {
        bird.reverseGravity();
    }

    if (IsKeyPressed(KEY_B))
    {
        isUpsideDown = !isUpsideDown;

        bird.setMode(isUpsideDown);

        for (int i = 0; i < MAX_PIPES; i++)
            if (pipes[i] != nullptr)
                pipes[i]->setMode(isUpsideDown);
    }

    if (state == GAMEOVER)
    {
        if (IsKeyPressed(KEY_R))
            startGame();

        if (IsKeyPressed(KEY_M))
            reset();

        if (IsKeyPressed(KEY_Q))
            CloseWindow();
    }
    if (IsKeyPressed(KEY_L)) {
        level++;
        startGame();
    }
}

void Game::update()
{
    float d = GetFrameTime();
    handleInput();
    if (state != PLAYING)
        return;
    bgX1 -= 100 * d;
    bgX2 -= 100 * d;

    if (bgX1 <= -background.width)
        bgX1 = bgX2 + background.width - 10;

    if (bgX2 <= -background.width)
        bgX2 = bgX1 + background.width - 10;

    bird.update(d);
    if (bird.checkCollision())
        state = GAMEOVER;

    for (int i = 0; i < MAX_PIPES; i++)
    {
        pipes[i]->update(d);

        if (pipes[i]->checkCollision(bird))
            state = GAMEOVER;

        if (pipes[i]->isPassed(bird))
            score++;
    }
    if (score >= 30 && level == 1)
    {
        level = 2;
        startGame();
    }
}

void Game::draw()
{
    Texture2D currentBG = isUpsideDown ? bgUD : bgNormal;
    DrawTexture(currentBG, bgX1, 0, WHITE);
    DrawTexture(currentBG, bgX2, 0, WHITE);
    if (state == MENU)
    {
        DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), Fade(BLACK, 0.7f));
        Rectangle panel = { 400, 120, 520, 400 };
        Color themeColor = isUpsideDown ? RED : MAROON;
        DrawRectangleRec(panel, Fade(themeColor, 0.1f));
        DrawRectangleLinesEx(panel, 4, themeColor);

        DrawText("THE UPSIDE DOWN", 430, 150, 50, themeColor);
        DrawText("B - TOGGLE WORLD", 470, 200, 25, GRAY); 


        DrawText("ENTER  -  START", 470, 250, 30, RAYWHITE);
        DrawText("SPACE  -  FLAP", 470, 300, 30, RAYWHITE);
        DrawText("U  -  NEXT LEVEL", 470, 350, 30, RAYWHITE);
        DrawText("Q  -  QUIT", 470, 400, 30, RAYWHITE);
    }

    else if (state == PLAYING)
    {
        bird.draw();
        for (int i = 0; i < MAX_PIPES; i++)
            pipes[i]->draw();

        DrawText(TextFormat("Score: %d", score), 20, 20, 30, BLACK);
        DrawText(TextFormat("Level: %d", level), 20, 60, 30, BLACK);
    }
    else if (state == GAMEOVER)
    {
        DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), Fade(BLACK, 0.6f));
        Rectangle panel = { 450, 180, 400, 300 };
        DrawRectangleRec(panel, Fade(RED, 0.15f));
        DrawRectangleLinesEx(panel, 4, RED);
        DrawText("YOU DIED", 520, 210, 50, RED);
        DrawText(TextFormat("Final Score: %d", score), 520, 280, 30, RAYWHITE);
        DrawText("R - Restart", 520, 330, 25, RAYWHITE);
        DrawText("M - Menu", 520, 370, 25, RAYWHITE);
        DrawText("Q - Quit", 520, 410, 25, RAYWHITE);
    }
}
