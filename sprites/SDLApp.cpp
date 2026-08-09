#include "SDLApp.hpp"
#include "SpriteComponent.hpp"

#include <iostream>

#include "SDL_image.h"

SDLApp::SDLApp() {
    this->sdlWindow = NULL;
    this->sdlRenderer = NULL;
    this->running = false;
}

int SDLApp::init() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        return -1;
    }

    this->sdlWindow = SDL_CreateWindow(
        "SDL Template",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED, 1100, 900,
        SDL_WINDOW_SHOWN
    );
    if (this->sdlWindow == NULL) {
        std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        return -1;
    }

    this->sdlRenderer = SDL_CreateRenderer(
        this->sdlWindow,
        -1,
        SDL_RENDERER_ACCELERATED
    );

    if (this->sdlRenderer == NULL) {
        std::cerr << "Renderer could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        return -1;
    }

    this->running = true;
    return 0;
}

SDL_Texture* SDLApp::createTexture(SDL_Renderer* renderer, const std::string& fileName) {

    SDL_Surface* surface = IMG_Load(fileName.c_str());
    if (!surface) {
        SDL_Log("Failed to load texture file %s", fileName.c_str());
        return nullptr;
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (!texture) {
        SDL_Log("Failed to convert surface to texture for %s", fileName.c_str());
        return nullptr;
    }

    SDL_FreeSurface(surface);
    return texture;
}

int SDLApp::run() {
    SDL_Event e;

    SDL_Texture* bubbleTexture = this->createTexture(this->sdlRenderer, "assets/bubble.png");
    SpriteComponent sprite(1.0f, {100, 100});
    sprite.setTexture(bubbleTexture);

    while (this->running) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                this->running = false;
            } else if (e.type == SDL_KEYDOWN) {
                    SDL_Keycode key = e.key.keysym.sym;
                    if (key == SDLK_q || key == SDLK_ESCAPE || key == SDLK_q) {
                        std::cout << "Key Q pressed (KEYDOWN)" << std::endl;
                        this->running = false;
                    }
                }
        }

        SDL_SetRenderDrawColor(this->sdlRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(this->sdlRenderer);

        // Render your content here
        sprite.render(this->sdlRenderer);

        SDL_RenderPresent(this->sdlRenderer);
        SDL_Delay(10);
    }

    return 0;
}

SDLApp::~SDLApp() {
    if (this->sdlRenderer != NULL) {
        SDL_DestroyRenderer(this->sdlRenderer);
    }

    if (this->sdlWindow != NULL) {
        SDL_DestroyWindow(this->sdlWindow);
    }
}
