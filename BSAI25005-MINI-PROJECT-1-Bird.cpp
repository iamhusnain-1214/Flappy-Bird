#include <raylib.h>
#include "BSAI25005-MINI-PROJECT-1-Game.h"

int main()
{
    InitWindow(1366, 768, "Flappy Bird - OOP Project");
    InitAudioDevice();
    SetTargetFPS(60);
    Music bgMusic = LoadMusicStream("run.mp3");
    SetMusicVolume(bgMusic, 0.9f);
    PlayMusicStream(bgMusic);
    Game game;
    while (!WindowShouldClose())
    {
        game.update();
        UpdateMusicStream(bgMusic);
        BeginDrawing();
        ClearBackground(RAYWHITE);

        game.draw();

        EndDrawing();
    }

    CloseWindow();

    return 0;
}
