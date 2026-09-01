#pragma once

#include <SDL3/SDL.h>

#define FRAME_RATE 60
#define FRAME_DELAY_MS 1000 / FRAME_RATE

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
};