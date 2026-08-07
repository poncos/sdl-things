#pragma once

#include <SDL2/SDL.h>

struct Point {
    float x;
    float y;
};

class EquilateralTriangle {
public:
    EquilateralTriangle(struct Point initialVertex, int height);
    ~EquilateralTriangle();

    void render(SDL_Renderer* renderer);

    struct Point vertex1;
    struct Point vertex2;
    struct Point vertex3;
    int height;
};