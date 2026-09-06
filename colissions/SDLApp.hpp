#pragma once

#include <SDL3/SDL.h>
#include <vector>

class SDLApp {
public:
    SDLApp();
    ~SDLApp();

    int init();
    int run();

    std::vector<class GameObject*> getGameObjects() const { return gameObjects; }

private: 
    bool running;

    SDL_Window* sdlWindow;
    SDL_Renderer* sdlRenderer;

    std::vector<GameObject*> gameObjects;

    int initModel();
};