#include "GameObject.hpp"

GameObject::GameObject( SDLApp* app, struct Vector2DF position, struct Vector2DF dimensions)
    : app(app), position(position), dimensions(dimensions) {
    // Initialize the bounding box component
    this->boundingBox = new SquareBoundingBox(this);
    this->moveComponent = new MoveComponent(this, {0, 0}, true, {1100, 900}, MoveComponent::ScreenBoundBehavior::WRAP_AROUND);

    this->objectId = reinterpret_cast<uint64_t>(this);
}

GameObject::~GameObject() {
    // Destructor implementation (if needed)
    delete this->boundingBox;
    delete this->moveComponent;
}

void GameObject::update(float deltaTime) {
    this->moveComponent->update(deltaTime);
}

void GameObject::render(SDL_Renderer* renderer) {
    // Render logic for the game object
    SDL_FRect rect;
    rect.x = static_cast<float>(this->position.x);
    rect.y = static_cast<float>(this->position.y);
    rect.w = static_cast<float>(this->dimensions.x);
    rect.h = static_cast<float>(this->dimensions.y);

    SDL_SetRenderDrawColor(renderer, this->color.x, this->color.y, this->color.z, 255);
    SDL_RenderFillRect(renderer, &rect);
}