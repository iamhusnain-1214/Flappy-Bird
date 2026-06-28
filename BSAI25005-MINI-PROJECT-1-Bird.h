#include "BSAI25005-MINI-PROJECT-1-Bird.h"
Bird::Bird()
{
    batTex = LoadTexture("flappy.png");
    normalTex = LoadTexture("demobat.png");
    texture = batTex;
    isBat = true;
    texture.height = 80;
    normalTex.width = 80;
    normalTex.height = 80;
    batTex.width = 80;
    batTex.height = 80;
    texture.width = 80;
    gravity = 900.0f;
    gravityDir = 1.0f;
    velocity = 0;
    rotation = 0;
    reset();
}
void Bird::reverseGravity()
{
    gravityDir *= -1;
}

void Bird::setMode(bool upside)
{
    isBat = upside;
    texture = upside ? batTex : normalTex;
}

void Bird::reset()
{
    position.x = 200;
    position.y = 300;

    velocity = 0;
    rotation = 0;
}
void Bird::flap()
{
    velocity = -350 * gravityDir;
}

void Bird::update(float delta)
{
    velocity += gravity * gravityDir * delta;
    position.y += velocity * delta;
    if (velocity * gravityDir < 0)
        rotation = -20;
    else
        rotation = 40;
}

void Bird::draw()
{
    Rectangle src = { 0, 0, (float)texture.width, (float)texture.height };
    Rectangle dest = {
        position.x,
        position.y,
        (float)texture.width,
        (float)texture.height
    };
    Vector2 origin = {
        texture.width / 2.0f,
        texture.height / 2.0f
    };
    DrawTexturePro(texture, src, dest, origin, rotation, WHITE);
}

bool Bird::checkCollision()
{
    if (position.y < 0 or position.y + texture.height > 798)
        return true;

    return false;
}

Rectangle Bird::getRect()
{
    return {
        position.x - texture.width / 2,
        position.y - texture.height / 2,
        (float)texture.width - 50,
        (float)texture.height - 60
    };
}
