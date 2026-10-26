#pragma once

#include <SDL3/SDL.h>

struct Point {
    float x;
    float y;
};

struct AnimationConfig {
    bool flashingEnabled = false;
    bool visible = true;
    int nonVisibleTimeMs = 0;
    int visibleTimeMs = 0;
    int delayTimeMs = 0;
    long lastTimeUpdated = 0L;

    AnimationConfig(){}

    AnimationConfig(bool flashing, bool visible, int visibleTimeMs, int nonVisibleTimeMs, int delayTimeMs)
    : flashingEnabled(flashing), visible (visible), visibleTimeMs(visibleTimeMs), nonVisibleTimeMs(nonVisibleTimeMs), delayTimeMs(delayTimeMs) {}
};

class SpriteComponent {

public:

    SpriteComponent(float scale = 1, struct Point position = {0, 0}) :
        scale(scale), texture(nullptr), position(position) { }
    ~SpriteComponent();
    virtual void update(float deltaTime);
    virtual void render(SDL_Renderer* renderer);
    void setTexture(SDL_Texture* texture);
    void setAnimationConfig(AnimationConfig config) {this->animationConfig = config; };

private:
    SDL_Texture* texture;
    float scale;
    struct Point position;
    int textureWidth;
    int textureHeight;
    AnimationConfig animationConfig;
};
