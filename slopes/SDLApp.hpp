#pragma once

#include <SDL3/SDL.h>
#include <array>

int constexpr windowWidth = 1100;
int constexpr windowHeight = 900;
int constexpr objectSize = 50;

class SDLApp {
public:

    SDLApp();
    ~SDLApp();

    int init();
    int run();

private: 
    bool running;

    SDL_Window* sdlWindow;
    SDL_Renderer* sdlRenderer;
    float x = 300;
    float y = windowHeight - objectSize;

    void renderBackground(SDL_Renderer* renderer);
    void renderObjects(SDL_Renderer* renderer);
    void handleBackgroundCollisions();
};