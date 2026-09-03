#include "SDLApp.hpp"
#include <iostream>

#include "MoveComponent.hpp"

SDLApp::SDLApp() {
    this->sdlWindow = NULL;
    this->sdlRenderer = NULL;
    this->running = false;
}

int SDLApp::init() {
    std::cout << "Initializing with frame rate: " << FRAME_DELAY_MS << std::endl;

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

int SDLApp::run() {
    SDL_Event e;
    
    while (this->running) {
         // We want to draw about 60 Frames Per Second (60 FPS).
        // So we wait until 16 milliseconds have passed since the last frame
        uint32_t frameStart = this->sdTimeWait(this->mTicksCount + FRAME_DELAY_MS);
        float deltaTimeSeconds = (frameStart - this->mTicksCount) / 1000.0;
        std::cout << "Preparing Frame with delta time: " << deltaTimeSeconds << " (seconds)" << std::endl;
        //  END 
        
        this->handleInputs();
        this->render();
        this->moveComponent.update(deltaTimeSeconds);
        this->mTicksCount = frameStart;
    }

    return 0;
}

int SDLApp::render() {
    SDL_SetRenderDrawColor(this->sdlRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderClear(this->sdlRenderer);

    // Render your content here
    this->object.x = this->moveComponent.getPosition().x;
    this->object.y = this->moveComponent.getPosition().y;

    SDL_SetRenderDrawColor(this->sdlRenderer, 0xFF, 0x00, 0x00, 0xFF);
    SDL_RenderFillRect(this->sdlRenderer, &this->object);
    SDL_RenderPresent(this->sdlRenderer);
    return 0;
}

int SDLApp::handleInputs() {

    SDL_Event e;

    while (SDL_PollEvent(&e)) {
        if (e.type == SDL_EVENT_QUIT) {
            this->running = false;
        } else if (e.type == SDL_EVENT_KEY_DOWN) {
            SDL_Keycode key = e.key.key;
            if (key == SDLK_Q || key == SDLK_ESCAPE) {
                std::cout << "Key Q or ESC pressed (KEYDOWN)" << std::endl;
                this->running = false;
            }
        }
    }
    return 0;
}

uint32_t SDLApp::sdTimeWait(Uint32 targetTicks) {
    while (SDL_GetTicks() < targetTicks) {
        SDL_Delay( 1 );
    }
    return SDL_GetTicks();
}

SDLApp::~SDLApp() {
    if (this->sdlRenderer != NULL) {
        SDL_DestroyRenderer(this->sdlRenderer);
    }

    if (this->sdlWindow != NULL) {
        SDL_DestroyWindow(this->sdlWindow);
    }
}
