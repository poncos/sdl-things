#include "SpriteComponent.hpp"

#include <iostream>

SpriteComponent::~SpriteComponent() {
    // No need to free the texture, as we don't own it
}

void SpriteComponent::render(SDL_Renderer* renderer) {
    
    if (this->texture == nullptr)
        return;

   std::cout << "Rendering SpriteComponent: " << this->flip << std::endl;
    SDL_Rect dest;
    dest.x = static_cast<int>(this->position.x);
    dest.y = static_cast<int>(this->position.y);
    dest.w = static_cast<int>(this->textureWidth * this->scale);
    dest.h = static_cast<int>(this->textureHeight * this->scale);

    SDL_RenderCopyEx(renderer, this->texture, nullptr, &dest,0,NULL, this->flip);
 }

void SpriteComponent::setTexture(SDL_Texture* texture) {
    this->texture = texture;

	// Set width/height
	SDL_QueryTexture(this->texture, 
        nullptr,
        nullptr,
        &this->textureWidth,
        &this->textureHeight
    );
}