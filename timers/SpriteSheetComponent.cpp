#include "SpriteSheetComponent.hpp"

#include <iostream>

void SpriteSheetComponent::setTextureList(std::vector<SDL_Texture*>& textures) {
    this->textureList = textures;

    if (this->textureList.size() > 0) {
        this->currentTexture = 0;
        this->setTexture(this->textureList[0]);
    }
}

void SpriteSheetComponent::update(float deltaTime) {

    //std::cout << "SpriteSheetComponent::update " << this->actor->getName() << std::endl;
    if (this->fps <= 0)
        this->currentTexture += 1;
    else
        this->currentTexture += deltaTime * this->fps;

    if (this->currentTexture >= this->textureList.size()) {
        this->currentTexture -= this->textureList.size();
    }

    this->setTexture(this->textureList[this->currentTexture]);
}

void SpriteSheetComponent::render(SDL_Renderer* renderer) {   
    SpriteComponent::render(renderer);
}
