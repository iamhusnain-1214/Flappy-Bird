#pragma once
#include <raylib.h>

class Bird
{
private:
    Vector2 position;
    float velocity;
    float gravity;
    float rotation;
    Texture2D texture;
    Texture2D batTex;
    Texture2D normalTex;
    float gravityDir;
    bool isBat;
public:
    Bird();
    void reverseGravity();
    void setMode(bool upside);
    void update(float delta);
    void flap();
    void draw();
    bool checkCollision();
    Rectangle getRect();
    void reset();
};




