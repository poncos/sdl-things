#include "MoveComponent.hpp"

#include <iostream>

void MoveComponent::update(float deltaTime) {
    std::cout << "MoveComponent::update with deltaTime: " << deltaTime  << " ge: " << this->gravityEnabled <<
        " Velocity: (" << this->velocity.x << ", " << this->velocity.y << ")" << 
        " Current Position: (" << this->position.x << ", " << this->position.y << ")" << std::endl;
    if (this->gravityEnabled) {
        this->velocity.y += GRAVITY * deltaTime;
    }

    this->position.x += this->velocity.x * deltaTime;
    this->position.y += this->velocity.y * deltaTime;

    enum Direction boundsCheck = this->checkBounds();
    switch (boundsCheck) {
        case Direction::UP:
            std::cout << "MoveComponent::update UP bounds check" << std::endl;
            if (this->velocity.y < 0) {
                this->position.y = 0;
                this->velocity.y = 0;
            }
            break;
        case Direction::DOWN:
            std::cout << "MoveComponent::update DOWN bounds check" << std::endl;
            if (this->velocity.y > 0) {
                this->position.y =
                    this->screenBounds.y - this->objectDimensions.y;
                this->velocity.y = 0;
            }
            break;
        case Direction::LEFT:
            std::cout << "MoveComponent::update LEFT bounds check" << std::endl;
            if (this->velocity.x < 0) {
                this->position.x = 0;
                this->velocity.x = 0;
            }
            break;
        case Direction::RIGHT:
            std::cout << "MoveComponent::update RIGHT bounds check" << std::endl;
            if (this->velocity.x > 0) {
                this->position.x =
                    this->screenBounds.x - this->objectDimensions.x;
                this->velocity.x = 0;
            }
            break;
        default:
            break;
    }
}

enum Direction MoveComponent::checkBounds() {

    if (this->screenBounds.x <= 0 || this->screenBounds.y <= 0)
        return Direction::NONE;

    if (this->position.x < 0) {
        return Direction::LEFT;
    } else if (this->position.x > this->screenBounds.x - this->objectDimensions.x) {
        return Direction::RIGHT;
    } else if (this->position.y < 0) {
        return Direction::UP;
    } else if (this->position.y > this->screenBounds.y - this->objectDimensions.y) {
        return Direction::DOWN;
    }

    return Direction::NONE;
}
