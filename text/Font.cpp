#include "Font.hpp"

#include <SDL.h>
#include <SDL_ttf.h>
#include <iostream>
#include <string>


Font::Font(const std::string& fileName, int fontSize) {
    this->fileName = fileName;

    // Initialize the font library
    if (TTF_Init() == -1) {
        std::cerr << "Failed to initialize TTF: " << TTF_GetError() << std::endl;
        return;
    }

    // Load the font
    this->font = TTF_OpenFont(fileName.c_str(), 20);
    if (!this->font) {
        std::cerr << "Failed to load font: " << TTF_GetError() << std::endl;
    }
}

SDL_Texture* Font::RenderText(
    SDL_Renderer* sdlRenderer,
    const std::string& text,
    struct Vector3f color,
    int fontSize) {

    std::cout << "Rendering text: " << text << " with color: (" << color.x << ", " << color.y << ", " << color.z << ") and font size: " << fontSize << std::endl;

    if (!this->font) {
        std::cerr << "Font not initialized." << std::endl;
        return nullptr;
    }

    // Set the font size
    if (fontSize > 0) {
        TTF_SetFontSize(this->font, fontSize);
    }

    // Create a surface with the text
    SDL_Color sdlColor = { static_cast<Uint8>(color.x * 255),
                           static_cast<Uint8>(color.y * 255),
                           static_cast<Uint8>(color.z * 255) };
    SDL_Surface* surface = TTF_RenderText_Solid(this->font, text.c_str(), sdlColor);
    if (!surface) {
        std::cerr << "Failed to create text surface: " << TTF_GetError() << std::endl;
        return nullptr;
    }

    // Create a texture from the surface
    SDL_Texture* texture = SDL_CreateTextureFromSurface(sdlRenderer, surface);
    SDL_FreeSurface(surface);

    if (!texture) {
        std::cerr << "Failed to create texture from surface: " << SDL_GetError() << std::endl;
        return nullptr;
    }

    return texture;
}

Font::~Font() {
    if (this->font) {
        TTF_CloseFont(this->font);
    }
    TTF_Quit();
}