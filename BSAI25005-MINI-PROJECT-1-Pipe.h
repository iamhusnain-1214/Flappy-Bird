#include "BSAI25005-MINI-PROJECT-1-Pipe.h"
#include <iostream>
using namespace std;


Pipe::Pipe(float _X, float gap, float spd)
{

    normalPipe = LoadTexture("plr.png");
    upsidePipe = LoadTexture("pipe.png");
    texture = normalPipe;
    texture.height = 650;
    texture.width = 90;
    upsidePipe.height = 650;
    upsidePipe.width = 90;
    normalPipe.height = 650;
    normalPipe.width = 90;
    x = _X;
    gapSize = gap + 10;
    speed = spd;
    passed = false;
    gapY = rand() % 300 + 150;
}
void Pipe::setMode(bool upside)
{
    texture = upside ? upsidePipe : normalPipe;
}

void Pipe::reset(float _X)
{

    x = _X;
    gapY = rand() % 300 + 150;
    passed = false;
}

void Pipe::draw()
{
    DrawTexture(texture, x, gapY - gapSize - texture.height, WHITE);
    DrawTexture(texture, x, gapY, WHITE);
}
bool Pipe::checkCollision(Bird& bird)
{
    Rectangle birdr = bird.getRect();
    Rectangle top = {
        x,
        gapY - gapSize - texture.height,
        (float)texture.width - 60,
        (float)texture.height - 55
    };
    Rectangle bottom = {
        x,
        gapY,
        (float)texture.width,
        (float)texture.height
    };
    if (CheckCollisionRecs(birdr, top) or CheckCollisionRecs(birdr, bottom))
        return true;

    return false;
}
void Pipe::update(float d)
{
    x -= speed * d;

    if (x + texture.width < 0)
        reset(GetScreenWidth() + 200);
}
bool Pipe::isPassed(Bird& bird)
{
    if (!passed and bird.getRect().x > x + texture.width)
    {
        passed = true;
        return true;
    }
    return false;
}