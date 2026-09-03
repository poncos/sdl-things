#pragma once

#include <SDL3/SDL.h>

#include "MoveComponent.hpp"

#define FRAME_RATE 60
#define FRAME_DELAY_MS 1000 / FRAME_RATE

#define SCREEN_WIDTH 1100
#define SCREEN_HEIGHT 900

class SDLApp {
public:
    SDLApp();
    ~SDLApp();

    int init();
    int run();
    int handleInputs();
    int render();

private: 
    bool running;

    uint32_t sdTimeWait(Uint32 targetTicks);
    Uint32 mTicksCount = 0;
    SDL_Window* sdlWindow;
    SDL_Renderer* sdlRenderer;
    SDL_FRect object = { 300, 40, 50, 50 };
    MoveComponent moveComponent =
        MoveComponent({ object.x, object.y }, { 0, 0 }, { 0, 0 }, { object.w, object.h }, true, { SCREEN_WIDTH, SCREEN_HEIGHT });
};