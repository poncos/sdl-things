#include "SDLApp.hpp"
#include "SpriteComponent.hpp"
#include "SpriteSheetComponent.hpp"

#include <iostream>
#include <SDL3_image/SDL_image.h>


SDLApp::SDLApp() {
    this->sdlWindow = NULL;
    this->sdlRenderer = NULL;
    this->running = false;
}

int SDLApp::init() {
    if (!SDL_InitSubSystem(SDL_INIT_VIDEO)) {
        std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        return -1;
    }

    this->sdlWindow = SDL_CreateWindow(
        "SDL Template",
        1100, 900,
        SDL_WINDOW_RESIZABLE
    );

    if (this->sdlWindow == NULL) {
        std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        return -1;
    }

    this->sdlRenderer = SDL_CreateRenderer(
        this->sdlWindow,
        NULL
    );

    if (this->sdlRenderer == NULL) {
        std::cerr << "Renderer could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        return -1;
    }

    this->running = true;
    return 0;
}

SDL_Texture* SDLApp::createTexture(SDL_Renderer* renderer, const std::string& fileName) {

    SDL_Texture* texture = IMG_LoadTexture(renderer, fileName.c_str());
    if (!texture) {
        SDL_Log("Failed to load texture file %s", fileName.c_str());
        return nullptr;
    }

    return texture;
}

int SDLApp::run() {

    SDL_Texture* bubbleTexture = this->createTexture(this->sdlRenderer, "assets/bubble.png");
    SpriteComponent sprite(1.0f, {100, 100});
    sprite.setTexture(bubbleTexture);
    sprite.setAnimationConfig(
        {true, true, 0, 2000}
    );
    SpriteComponent sprite2(1.0f, {250, 100});
    sprite2.setTexture(bubbleTexture);
    sprite2.setAnimationConfig(
        {true, true, 2000, 2000}
    );
    SpriteComponent sprite3(1.0f, {400, 100});
    sprite3.setTexture(bubbleTexture);
    sprite3.setAnimationConfig(
        {true, true, 4000, 2000}
    );
    SpriteComponent sprite4(1.0f, {550, 100});
    sprite4.setTexture(bubbleTexture);
    sprite4.setAnimationConfig(
        {true, true, 6000, 2000}
    );

    while (this->running) {
        // We want to draw about 60 Frames Per Second (60 FPS).
        // So we wait until 16 milliseconds have passed since the last frame
        uint32_t frameStart = this->sdlTimeWait(this->mTicksCount + FRAME_DELAY_MS);
        float deltaTimeSeconds = (frameStart - this->mTicksCount) / 1000.0f;
        this->mTicksCount = frameStart;
        std::cout << "Preparing Frame with delta time: " << deltaTimeSeconds << " (seconds)" << std::endl;
        //  END

        this->input();

        sprite.update(deltaTimeSeconds);
        sprite2.update(deltaTimeSeconds);
        sprite3.update(deltaTimeSeconds);
        sprite4.update(deltaTimeSeconds);

        SDL_SetRenderDrawColor(this->sdlRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(this->sdlRenderer);

        // Render your content here
        sprite.render(this->sdlRenderer);
        sprite2.render(this->sdlRenderer);
        sprite3.render(this->sdlRenderer);
        sprite4.render(this->sdlRenderer);

        SDL_RenderPresent(this->sdlRenderer);
    }

    return 0;
}

uint32_t SDLApp::sdlTimeWait(Uint32 targetTicks) {
    while (SDL_GetTicks() < targetTicks) {
        SDL_Delay( 1 );
    }
    return SDL_GetTicks();
}

int SDLApp::input() {
    SDL_Event e;

    while (SDL_PollEvent(&e) != 0) {
        if (e.type == SDL_EVENT_QUIT) {
            this->running = false;
        } else if (e.type == SDL_EVENT_KEY_DOWN) {
                SDL_Keycode key = e.key.key;
                if (key == SDLK_Q || key == SDLK_ESCAPE) {
                    std::cout << "Key Q pressed (KEYDOWN)" << std::endl;
                    this->running = false;
                }
            }
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
