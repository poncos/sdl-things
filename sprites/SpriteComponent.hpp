#pragma once

#include <SDL.h>

struct Point {
    float x;
    float y;
};

class SpriteComponent {

public:

    SpriteComponent(float scale = 1, struct Point position = {0, 0}) :
        scale(scale), texture(nullptr), position(position) { }
    ~SpriteComponent();
    virtual void update(float deltaTime) {};
    virtual void render(SDL_Renderer* renderer);
    void setTexture(SDL_Texture* texture);

protected:
    SDL_RendererFlip flip = SDL_FLIP_NONE;

private:
    SDL_Texture* texture;
    float scale;
    struct Point position;
    int textureWidth;
    int textureHeight;
};
