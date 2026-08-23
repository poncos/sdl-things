#pragma once

#include <SDL3_ttf/SDL_ttf.h>
#include <SDL3/SDL.h>
#include <iostream>
#include <string>

struct Vector3f {
    float x;
    float y;
    float z;
};

class Font {
public:
    Font(const std::string& fileName, int fontSize = 20);
    ~Font();

    SDL_Texture* RenderText(
        SDL_Renderer* sdlRenderer,
        const std::string& text,
        struct Vector3f color = { 1.0f, 1.0f, 1.0f },
        int fontSize = -1);
private:
    TTF_Font* font = nullptr;
    std::string fileName;
};