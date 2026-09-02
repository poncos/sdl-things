#include "MoveComponent.hpp"

void MoveComponent::update(float deltaTime) {
    if (this->gravityEnabled) {
        this->velocity.y += GRAVITY * deltaTime;
    }

    enum Direction boundsCheck = this->checkBounds();
    switch (boundsCheck) {
        case Direction::UP:
            if (this->velocity.y < 0) {
                this->velocity.y = 0;
            }
            break;
        case Direction::DOWN:
            if (this->velocity.y > 0) {
                this->velocity.y = 0;
            }
            break;
        case Direction::LEFT:
            if (this->velocity.x < 0) {
                this->velocity.x = 0;
            }
            break;
        case Direction::RIGHT:
            if (this->velocity.x > 0) {
                this->velocity.x = 0;
            }
            break;
        default:
            break;
    }
    
    this->position.x += this->direction.x * this->velocity.x * deltaTime;
    this->position.y += this->direction.y * this->velocity.y * deltaTime;
}

enum Direction MoveComponent::checkBounds() {

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
