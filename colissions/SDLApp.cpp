#include "SDLApp.hpp"

#include "GameObject.hpp"

#include <iostream>


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

    return this->initModel(); // Initialize the game model (create GameObjects)
}

int SDLApp::initModel() {
    // Create two GameObjects with different positions and dimensions
    GameObject* obj1 = new GameObject(this, {100, 100}, {50, 50});
    GameObject* obj2 = new GameObject(this, {120, 120}, {50, 50});

    // Add them to the gameObjects vector
    this->gameObjects.push_back(obj1);
    this->gameObjects.push_back(obj2);

    return 0;
}

int SDLApp::run() {
    SDL_Event e;
    uint32_t lastTime = SDL_GetTicks();

    while (this->running) {
        uint32_t currentTime = SDL_GetTicks();
        float deltaTime = (currentTime - lastTime) / 1000.0f;
        lastTime = currentTime;

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

        SDL_SetRenderDrawColor(this->sdlRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(this->sdlRenderer);

        // Render your content here
        for (auto obj : this->gameObjects) {
            obj->update(deltaTime);
        }

        for (auto obj : this->gameObjects) {
            obj->render(this->sdlRenderer);
        }

        SDL_RenderPresent(this->sdlRenderer);
        SDL_Delay(15);
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

    for (auto obj : this->gameObjects) {
        delete obj;
    }
}
