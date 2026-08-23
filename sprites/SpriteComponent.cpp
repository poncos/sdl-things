#include "SpriteComponent.hpp"

#include <iostream>

SpriteComponent::~SpriteComponent() {
    // No need to free the texture, as we don't own it
}

void SpriteComponent::render(SDL_Renderer* renderer) {
    
    if (this->texture == nullptr)
        return;

//    std::cout << "Rendering SpriteComponent: " << this->flip << std::endl;
    SDL_FRect dest;
    dest.x = this->position.x;
    dest.y = this->position.y;
    dest.w = this->textureWidth * this->scale;
    dest.h = this->textureHeight * this->scale;

    SDL_RenderTexture(renderer, this->texture, nullptr, &dest);
 }

void SpriteComponent::setTexture(SDL_Texture* texture) {
    this->texture = texture;

	// Set width/height
	SDL_PropertiesID props = SDL_GetTextureProperties(this->texture);
    if (props == 0) {
        std::cerr << "Failed to get texture properties: " << SDL_GetError() << std::endl;
        return;
    }

	this->textureWidth =SDL_GetNumberProperty(props, SDL_PROP_TEXTURE_WIDTH_NUMBER, -1);
	this->textureHeight = SDL_GetNumberProperty(props, SDL_PROP_TEXTURE_HEIGHT_NUMBER, -1);

    if (this->textureWidth <= 0 || this->textureHeight <= 0) {
        std::cerr << "Invalid texture dimensions: " << this->textureWidth << "x" << this->textureHeight << std::endl;
        return;
    }
}