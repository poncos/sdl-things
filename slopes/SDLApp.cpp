#include "SDLApp.hpp"
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
    return 0;
}

int SDLApp::run() {
    SDL_Event e;



    while (this->running) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_EVENT_QUIT) {
                this->running = false;
            } else if (e.type == SDL_EVENT_KEY_DOWN) {
                SDL_Keycode key = e.key.key;
                if (key == SDLK_Q || key == SDLK_ESCAPE) {
                    std::cout << "Key Q or ESC pressed (KEYDOWN)" << std::endl;
                    this->running = false;
                }
                if (key == SDLK_RIGHT) {
                    this->x+=5;
                }
                if (key == SDLK_LEFT) {
                    this->x-=5;
                }
                if (key == SDLK_UP) {
                    this->y-=5;
                }
                if (key == SDLK_DOWN) {
                    this->y+=5;
                }
            }
        }

        this->handleBackgroundCollisions();

        SDL_SetRenderDrawColor(this->sdlRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(this->sdlRenderer);

        this->renderBackground(this->sdlRenderer);
        this->renderObjects(this->sdlRenderer);


        SDL_RenderPresent(this->sdlRenderer);
        SDL_Delay(10);
    }

    return 0;
}

void SDLApp::renderBackground(SDL_Renderer* renderer) {

    SDL_Vertex* verticesObject1 = new SDL_Vertex[4];
    verticesObject1[0] = {windowWidth/2, windowHeight};
    verticesObject1[1] = {windowWidth/2+300, windowHeight - 100};
    verticesObject1[2] = {windowWidth/2+300, windowHeight};

    SDL_RenderGeometry(renderer, NULL, verticesObject1, 3, NULL, 0);

    SDL_FRect object2 = { windowWidth/2+300, windowHeight - 100, windowWidth - windowWidth/2+300, 100 };
    SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
    SDL_RenderFillRect(renderer, &object2);
}

void SDLApp::renderObjects(SDL_Renderer* renderer) {
    SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0xFF);
    SDL_FRect object = { x, y, objectSize, objectSize };
    SDL_RenderFillRect(renderer, &object);
}

void SDLApp::handleBackgroundCollisions() {

    int objectMidelPos = this->x + objectSize/2;
    int slopeStartPos = windowWidth/2;
    int slopeEndPos = slopeStartPos + 300;

    if (objectMidelPos < slopeStartPos)
        return;
    if (objectMidelPos >= slopeStartPos && objectMidelPos < slopeEndPos) {
        //this->x = slopeStartPos - objectSize/2;

        float m = 100.0/300.0;
        std::cout << "Slope: " << m << std::endl;
        
        float dx = objectMidelPos - slopeStartPos;
        float dy = dx * m;
        this->y = windowHeight - dy - objectSize;
    }
}

SDLApp::~SDLApp() {
    if (this->sdlRenderer != NULL) {
        SDL_DestroyRenderer(this->sdlRenderer);
    }

    if (this->sdlWindow != NULL) {
        SDL_DestroyWindow(this->sdlWindow);
    }
}
