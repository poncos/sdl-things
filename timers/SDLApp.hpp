#pragma once

#include <SDL3/SDL.h>
#include <string>

#define FRAME_RATE 60
#define FRAME_DELAY_MS 1000 / FRAME_RATE

class SDLApp {
public:
    SDLApp();
    ~SDLApp();

    int input();
    int init();
    int run();

private: 
    bool running;

    SDL_Window* sdlWindow;
    SDL_Renderer* sdlRenderer;
    Uint32 mTicksCount = 0;

    uint32_t sdlTimeWait(Uint32 targetTicks);
    SDL_Texture* createTexture(SDL_Renderer* renderer, const std::string& fileName);
};