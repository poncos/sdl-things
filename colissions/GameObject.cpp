#include "GameObject.hpp"

GameObject::GameObject(struct Vector2DF position, struct Vector2DF dimensions)
    : position(position), dimensions(dimensions) {
    // Initialize the bounding box component
    this->boundingBox = new SquareBoundingBox(this);
}

GameObject::~GameObject() {
    // Destructor implementation (if needed)
    delete this->boundingBox;
}

void GameObject::update(float deltaTime) {
    // Update logic for the game object
}

void GameObject::render(SDL_Renderer* renderer) {
    // Render logic for the game object
}