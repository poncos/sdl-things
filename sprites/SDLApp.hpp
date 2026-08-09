#pragma once

#include <SDL2/SDL.h>
#include <string>

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

    SDL_Texture* createTexture(SDL_Renderer* renderer, const std::string& fileName);
};