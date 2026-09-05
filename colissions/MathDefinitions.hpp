#pragma once

#define GRAVITY 900.0f // pixels per second squared

struct Vector2DF {
    float x;
    float y;
};

struct Vector2DI {
    int x;
    int y;
};

enum class Direction {
    UP,
    DOWN,
    LEFT,
    RIGHT,
    NONE
};
