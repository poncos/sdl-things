#include "GameObject.hpp"

#include <iostream>

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

    this->handleCollision();
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

void GameObject::handleCollision() {
    this->app->getGameObjects();

    for (auto otherObject : this->app->getGameObjects()) {
        if (otherObject == this) {
            std::cout << "Skipping self in collision check for object ID: " << this->objectId << std::endl;
            continue; // Skip self
        }

        SquareBoundingBox::CollisionType collisionType = this->boundingBox->intersect(*otherObject->getBoundingBox());
        std::cout << "Collision result between object ID: " << this->objectId
                      << " and object ID: " << otherObject->getBoundingBox()
                      << " Collision Type: " << collisionType << std::endl;
        if (collisionType != SquareBoundingBox::CollisionType::NONE) {
             switch (collisionType) {
                case SquareBoundingBox::CollisionType::TOP:
                    std::cout << "Collision at the TOP of object ID: " << this->objectId << std::endl;
                    if (this->moveComponent->getSpeed().y < 0) {
                        this->moveComponent->setSpeed({
                            this->moveComponent->getSpeed().x,
                            this->moveComponent->getSpeed().y * -1});
                    }
                    
                    break;
                case SquareBoundingBox::CollisionType::BOTTOM:
                    std::cout << "Collision at the BOTTOM of object ID: " << this->objectId << std::endl;
                    if (this->moveComponent->getSpeed().y > 0) {
                        this->moveComponent->setSpeed({
                            this->moveComponent->getSpeed().x,
                            this->moveComponent->getSpeed().y * -1});
                    }
                    break;
                default:
                    break;
            }
        }
    }
}