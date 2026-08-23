#pragma once

#include <SDL3/SDL.h>

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

};