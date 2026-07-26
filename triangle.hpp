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

    struct Point initialVertex;
    int height;
};